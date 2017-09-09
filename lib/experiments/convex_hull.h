
/*
 * Created by Yaser Alkayale on 2017-07-19.
 *
 * Calculate the convex hull of a given Matrix.
 * Helper method uses the shoelace method to calculate the area of the hull
 *
 */

#ifndef KMEANSII_CONVEX_HULL_H
#define KMEANSII_CONVEX_HULL_H

#include <cassert>
#include <cmath>
#include "../algorithm/kmeans_data.h"
#include "../algorithm/kmeans_utils.h"

namespace kmeans{
namespace experiments{

Matrix<double> calculateConvexHull(Matrix<double> dataset);
/*
 * Take a convex hull and calculate its area.
 * This uses the shoelace method.
 * Assumes the dataset is sorted in clockwise order.
 *
 */
double convexHullArea(const Matrix<double> &dataset);

}//namespace experiments
}//namespace kmeans



#endif //KMEANSII_CONVEX_HULL_H
