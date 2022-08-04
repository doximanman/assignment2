//
// Created by kalo3 on 27-Jul-22.
//

#include "EuclideanDistance.hpp"
#include "Distance.hpp"
#include <cmath>

using namespace Geometry;

double EuclideanDistance::distance(Point p1, Point p2) {
    int dimension = p1.dimension;
    double sumOfSquares = 0;
    for (int i = 0; i < dimension; i++) {
        double difference = p1.at(i) - p2.at(i);
        sumOfSquares += difference * difference;
    }
    return sqrt(sumOfSquares);
}