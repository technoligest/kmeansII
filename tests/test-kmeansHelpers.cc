//
// Created by Yaser Alkayale on 2017-07-10.
//

#include "catch.hpp"
#include "../lib/Algorithm/KmeansHelpers.hh"

using namespace KmeansHelpers;
using namespace std;
using namespace KmeansData;

TEST_CASE("Analyzing Dataset Works"){
  KmeansData::Dataset d;
  REQUIRE(analyzeDataset(d));

  KmeansData::Instance i{1, 2};
  d.push_back(i);
  REQUIRE(analyzeDataset(d));

  d.clear();
  d.push_back({1, 2, 3, 4, 5});
  REQUIRE(analyzeDataset(d));

  d.clear();
  d.push_back({1});
  d.push_back({1, 2, 3});
  REQUIRE(!analyzeDataset(d));

  d.clear();
  d.push_back({1, 2});
  d.push_back({1, 4});
  d.push_back({3, 6});
  REQUIRE(analyzeDataset(d));

  d.push_back({1});
  REQUIRE(!analyzeDataset(d));

  d[0] = {1};
  REQUIRE(!analyzeDataset(d));
}

TEST_CASE("findDistance works"){
  cout << fixed;
  Instance l;
  Instance r;
  REQUIRE(l.empty());
  REQUIRE(r.empty());
  SECTION("Distance for 1-d points works"){
    l = {5};
    r = {10};
    REQUIRE(findDistanceSquared(l, r) == 25);
    REQUIRE(findDistanceSquared(r, l) == 25);
    REQUIRE(findDistanceSquared(l, l) == 0);
    REQUIRE(findDistanceSquared(r, r) == 0);
  }


  SECTION("Distance for 2-d points works."){
    l = {1, 2};
    r = {3, 2};
    REQUIRE(findDistanceSquared(l, r) == 4);
    REQUIRE(findDistanceSquared(r, l) == 4);
    REQUIRE(findDistanceSquared(l, l) == 0);
    REQUIRE(findDistanceSquared(r, r) == 0);
  }
  SECTION("Distance for 5-d points works."){
    l = {12, 17, 81, 44, 65};
    r = {23, 1, 32, 22, 43};
    REQUIRE(findDistanceSquared(l, r) == 3746);
    REQUIRE(findDistanceSquared(r, l) == 3746);
    REQUIRE(findDistanceSquared(l, l) == 0);
    REQUIRE(findDistanceSquared(r, r) == 0);

  }
  SECTION("Distance for 5-d double points works"){
    l = {2.1, 14.3, 12.3, 18.99, 99.8765};
    r = {13.6, 73.24, 123.76, 1234.12, 0.24};
    REQUIRE(findDistanceSquared(l, r) - 1502497.854232 < 1e-2);
    REQUIRE(findDistanceSquared(r, l) - 1502497.854232 < 1e-2);
    REQUIRE(findDistanceSquared(l, l) == 0);
    REQUIRE(findDistanceSquared(r, r) == 0);
  }
  SECTION("Distance between differently sized points works"){
    l = {1};
    r = {17, 13};
    REQUIRE(findDistanceSquared(l, r) == -1);
    REQUIRE(findDistanceSquared(r, l) == -1);
    REQUIRE(findDistanceSquared(l, l) == 0);
    REQUIRE(findDistanceSquared(r, r) == 0);

    l = {};
    r = {12, 18, 77};
    REQUIRE(findDistanceSquared(l, r) == -1);
    REQUIRE(findDistanceSquared(r, l) == -1);
    REQUIRE(findDistanceSquared(l, l) == 0);
    REQUIRE(findDistanceSquared(r, r) == 0);
  }
}

TEST_CASE("Preparing for clustering works."){
  Dataset d;
  Dataset c;
  Weights w;
  ull k = 0;
  REQUIRE(d.size() == 0);
  REQUIRE(c.size() == 0);
  REQUIRE(w.size() == 0);
  REQUIRE(!prepareForClustering(d, c, w, k));

  SECTION("Cannot prepare because the dataset is empty"){
    c.push_back({12});
    w.push_back(18);
    k = 1;
    REQUIRE(!prepareForClustering(d, c, w, k));
  }
  SECTION("Cannot prepare for clustering if k is higher than the dataset size."){
    d.push_back({1, 2, 3});
    d.push_back({1, 2, 3});
    k = 4;
    REQUIRE(!prepareForClustering(d, c, w, k));
    k = 5;
    REQUIRE(!prepareForClustering(d, c, w, k));
    k = 17;
    REQUIRE(!prepareForClustering(d, c, w, k));
    d.push_back({1, 3, 5});
    REQUIRE(!prepareForClustering(d, c, w, k));
    d.push_back({3, 4, 5});
    REQUIRE(!prepareForClustering(d, c, w, k));
  }

  SECTION("Cannot prepare for clustering because k is 0."){
    d.push_back({1});
    c.push_back({12});
    w.push_back(12);
    k = 0;
    REQUIRE(!prepareForClustering(d, c, w, k));
  }
  SECTION("Cannot prepare for clustering because the size of the weights is not the same as the dataset size."){
    d.push_back({2, 2});
    d.push_back({2, 2});
    c.push_back({0});
    w = {19, 20, 14};
    k = 1;
    REQUIRE(!prepareForClustering(d, c, w, k));

    w = {12};
    REQUIRE(!prepareForClustering(d, c, w, k));
  }
  SECTION("Can prepare for clustering if k and size of d is 1."){
    d.push_back({1});
    k = 1;
    REQUIRE(!prepareForClustering(d, c, w, k));
  }
  SECTION("Centres are resized properly"){
    d.push_back({1, 2});
    d.push_back({3, 4});
    d.push_back({19, 13});
    w = {1, 1, 1};

    k = 2;
    REQUIRE(prepareForClustering(d, c, w, k));
    REQUIRE(c.size() == k);

    k = 3;
    REQUIRE(prepareForClustering(d, c, w, k));
    REQUIRE(c.size() == k);
  }
}

TEST_CASE("Find belonging centre position works."){
  /*
   * It is crucial that the find distance method
   * is thoroughly tested beforehand.
   */

  Dataset c;
  Instance i;
  SECTION("Closest centre to an instance is chosen properly in 1-d."){
    c.push_back({1});
    c.push_back({4});
    c.push_back({6});
    i = {2};
    REQUIRE(findBelongingCentrePosition(i, c) == 0);
    i = {3};
    REQUIRE(findBelongingCentrePosition(i, c) == 1);
    i = {1};
    REQUIRE(findBelongingCentrePosition(i, c) == 0);
    i = {5};
    size_t temp = findBelongingCentrePosition(i, c);
    bool b = (temp == 1 || temp == 2);
    REQUIRE(b);

    for(int k = 7; k < 10234; ++k){
      i.clear();
      i.push_back(k);
      REQUIRE(findBelongingCentrePosition(i, c) == 2);
    }
  }
  SECTION("Closest centre to an instance is chosen properly in 2-d"){
    c.push_back({1, 1});
    c.push_back({-1, -1});
    c.push_back({1, -1});
    c.push_back({-1, 1});
    i = {0, 0};
    size_t temp = findBelongingCentrePosition(i, c);
    bool b = temp == 0 || temp == 1 || temp == 2 || temp == 3;
    REQUIRE(b);

    i = {0, 10};
    temp = findBelongingCentrePosition(i, c);
    b = temp == 0 || temp == 2;
    REQUIRE(b);

    i = {1, 0.5};
    REQUIRE(findBelongingCentrePosition(i, c) == 0);

    i = {-1, 0.5};
    REQUIRE(findBelongingCentrePosition(i, c) == 3);

    i = {10000, 10000};
    REQUIRE(findBelongingCentrePosition(i, c) == 0);
  }
}

TEST_CASE("Find shortest distance to clusterCentre"){
  /*
   * It is crucial that the find distance method
   * is thoroughly tested beforehand.
   */

  Dataset c;
  Instance i;
  SECTION("Distance to closest centre is calculated properly in 1-d."){
    c.push_back({1});
    c.push_back({4});
    c.push_back({6});
    i = {2};
    REQUIRE(shortestDistanceToClusterCentre(i, c) == 1);
    i = {3.5};
    REQUIRE(fabs(shortestDistanceToClusterCentre(i, c) - 0.25) < 1e-5);
    i = {1};
    REQUIRE(shortestDistanceToClusterCentre(i, c) == 0);
    i = {5.2};
    REQUIRE(fabs(shortestDistanceToClusterCentre(i, c) - 0.64) < 1e-5);

    for(int k = 7; k <= 21343; ++k){
      i.clear();
      i.push_back(k);
      shortestDistanceToClusterCentre(i, c) == ((k - 6) * (k - 6));
    }
  }
  SECTION("Closest centre to an instance is chosen properly in 2-d"){
    c.push_back({1, 1});
    c.push_back({-1, -1});
    c.push_back({1, -1});
    c.push_back({-1, 1});

    i = {0, 0};
    REQUIRE(shortestDistanceToClusterCentre(i, c) == 2);

    i = {0, 10};
    REQUIRE(fabs(shortestDistanceToClusterCentre(i, c) - 81.999997) < 1e-3);

    i = {1, 0.5};
    REQUIRE(fabs(shortestDistanceToClusterCentre(i, c) - 0.25) < 1e-6);

    i = {-1, 0.5};
    REQUIRE(fabs(shortestDistanceToClusterCentre(i, c) - 0.25) < 1e-6);

    i = {10000, 10000};
    REQUIRE(fabs(shortestDistanceToClusterCentre(i, c) - 199960001.995) < 1e-2);
  }
}

TEST_CASE("Calculating the objective function works well"){
  Dataset d;
  Dataset c;
  Weights w;
  SECTION("Calculations are proper with empty centres."){
    REQUIRE(calcDX(d, c, w) == -1);
    d.push_back({1});
    REQUIRE(calcDX(d, c, w) == -1);
    w.push_back(1);
    w.push_back(2);
    REQUIRE(calcDX(d, c, w) == -1);
  }
  SECTION("Calculations works well with 1-d points."){
    c.push_back({1});
    c.push_back({0});
    c.push_back({-5});

    d.push_back({2});
    d.push_back({0.5});
    d.push_back({-1});
    d.push_back({-2.5});
    d.push_back({-6});
    w = {1, 1, 1, 1, 1};
    REQUIRE(fabs(calcDX(d, c, w) - 9.5) < 1e-3);
  }
  SECTION("Calculation works well with 2-d points "){
    c.push_back({1, 1});
    c.push_back({-1, -1});
    c.push_back({-1, 1});
    c.push_back({1, -1});
  }
}