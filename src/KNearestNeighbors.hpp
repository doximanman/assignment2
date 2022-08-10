//
// Created by kalo3 on 28-Jul-22.
//

#ifndef ASS1_KNEARESTNEIGHBORS_HPP
#define ASS1_KNEARESTNEIGHBORS_HPP

#include "Distance.hpp"
#include <array>
using namespace Geometry;

class KNearestNeighbors {
private:
    /**
     * vector of Point vectors where the first dimension is the data
     * type, and the second dimension is the data of that type.
     */
    vector<vector<Point>> _data;
    Point _modelPoint;
    /**
     * returns the indices of the K closest points to the model point.
     * @return
     */
    vector<array<int,2>> firstK(int K, Distance &distance);
    /**
     * @param list
     * @param value
     * @return whether value is in list.
     */
    static bool contains(vector<array<int,2>> list, int val1,int val2);
    /**
     * total number of points in the data table.
     */
    int numOfPoints;

public:
    /**
     * Constructs the data table and the model point according to the given values.
     * @param modelPoint
     * @param data
     */
    KNearestNeighbors(const Point& modelPoint, vector<vector<Point>> data);
    /**
     * @param distance Distance function
     * @return a table of all the distances from the point (according to the data table -
     *         in the same order)
     */
    vector<vector<double>> distances(Distance &distance);
    /**
     * @param K
     * @param distance
     * @return K nearest neighbors, in accordance with the provided distance function.
     */
    vector<Point> nearestNeighbors(int K, Distance &distance);

    // returns the index of the determined data type.
    /**
     * Classifies the point according to the closest K points - the
     * type that has the most points from the K points will be the classification.
     * @param K
     * @param distance
     * @return the classification.
     */
    int classify(int K,Distance &distance);
    /**
     * Prints the K nearest members, according to the distance function.
     * @param K
     * @param distance
     */
    void printNearestNeighbors(int K,Distance &distance);
    static vector<string> classifyData(int k,
                                       Geometry::Distance &distance,
                                       const vector<vector<Geometry::Point>> &classifiedData,
                                              const vector<Geometry::Point> &unclassifiedData);
};

#endif //ASS1_KNEARESTNEIGHBORS_HPP
