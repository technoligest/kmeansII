//
// Created by Yaser Alkayale on 2017-07-12.
//

#include "kmeans_data.h"
#include <cassert>

namespace kmeans{

void operator/=(Instance &output_vector, const std::vector<size_t> &dividing_vector) {
  assert(output_vector.size() == dividing_vector.size());
  for(int i = 0; i < output_vector.size(); ++i) {
    output_vector[i] /= dividing_vector[i];
  }
};

void operator+=(Instance &output_vector, const Instance &adding_vector) {
  assert(output_vector.size() == adding_vector.size());
  for(int i = 0; i < output_vector.size(); ++i) {
    output_vector[i] += adding_vector[i];
  }
}

void operator-=(Instance &outpur_vector, const Instance &subtracting_vector) {
  assert(outpur_vector.size() == subtracting_vector.size());
  for(int i = 0; i < outpur_vector.size(); ++i) {
    outpur_vector[i] -= subtracting_vector[i];
  }
}

void operator*=(Instance &output_vector, const Instance &multiplying_vector) {
  assert(output_vector.size() == multiplying_vector.size());
  for(int i = 0; i < output_vector.size(); ++i) {
    output_vector[i] *= multiplying_vector[i];
  }
}

void operator/=(Instance &output_vector, const Instance &dividing_vector) {
  assert(output_vector.size() == dividing_vector.size());
  for(int i = 0; i < output_vector.size(); ++i) {
    output_vector[i] += dividing_vector[i];
  }
}

}//namespace kmeans