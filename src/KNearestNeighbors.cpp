//
// Created by kalo3 on 28-Jul-22.
//

#include <cstdlib>
#include <utility>
#include "KNearestNeighbors.hpp"
#include <iostream>
#include <array>

using namespace Geometry;
KNearestNeighbors::KNearestNeighbors(const Point& modelPoint,
                                     vector<vector<Point>> data) : _modelPoint(modelPoint),
                                                                   _data(std::move(data)) {
    int num=0;
    // goes to each data type and counts how many points there are in total.
    for(const auto& item:_data){
        num+=(int)item.size();
    }
    numOfPoints=num;
}
vector<vector<double>> KNearestNeighbors::distances(Distance &distance) {
    // instantiates the distance table.
    vector<vector<double>> dists(_data.size());
    for (int i = 0; i < _data.size(); i++) {
        // instantiates the data list of this type.
        dists.at(i)=vector<double>(_data.at(i).size());
        for (int j = 0; j < _data.at(i).size(); j++) {
            // sets [i][j] of the table to be the distance between the model point and data[i][j].
            dists.at(i).at(j) = distance.distance(_data.at(i).at(j), _modelPoint);
        }
    }
    return dists;
}

bool KNearestNeighbors::contains(vector<array<int,2>> list, int val1, int val2) {
    for (auto &item: list) {
        if (item[0] == val1 && item[1] == val2) {
            return true;
        }
    }
    return false;
}

vector<array<int,2>> KNearestNeighbors::firstK(int K, Distance &distance) {
    if(K>numOfPoints){
        K=numOfPoints;
    }
    vector<array<int,2>> result(K);
    for(auto item : result){
        item[0]=-1;
        item[1]=-1;
    }
    vector<vector<double>> dists = distances(distance);
    // finds the minimum K times - ignores the last findings (to make sure we get K different elements,
    // and not just the smallest element K times).
    for (int r = 0; r < K; r++) {
        // initialized at infinity so that we're guaranteed to have a number smaller than it.
        double min = 0x7fffffffL;
        int index1=-1;
        int index2=-1;
        for (int i = 0; i < dists.size(); i++) {
            for (int j = 0; j < dists.at(i).size(); j++) {
                // if(distance is smaller than the minimum we found && we didn't find this point before as a minimum)
                if (dists.at(i).at(j) < min && (!contains(result, i,j))) {
                    // save the indices and minimum as the new minimum.
                    index1 = i;
                    index2 = j;
                    min = dists.at(i).at(j);
                }
            }
        }
        // the indices of the new minimum.
        result.at(r)[0] = index1;
        result.at(r)[1] = index2;
    }
    return result;
}

vector<Point> KNearestNeighbors::nearestNeighbors(int K, Distance &distance) {
    // simply gets the indices of the nearest neighbors and returns a list of the actual points.
    vector<Point> neighbors={};
    vector<array<int,2>> indices = firstK(K, distance);
    for (auto & index : indices) {
        neighbors.push_back(_data.at(index[0]).at(index[1]));
    }
    return neighbors;
}

int KNearestNeighbors::classify(int K, Distance &distance) {
    // uses a counter list to count how many points of the closest K points are of each
    // data type, then finds the max of that counter list, and returns the index of it.
    vector<array<int,2>> neighborIndices = firstK(K, distance);
    // counter list.
    vector<int> counter(_data.size());
    // initializes at 0.
    for (int i = 0; i < _data.size(); i++) {
        counter.at(i) = 0;
    }
    // adds 1 for every occurrence.
    for (auto &index: neighborIndices) {
        counter.at(index[0])++;
    }
    // finds max.
    int max = -1;
    int maxType=-1;
    for (int i = 0; i < _data.size(); i++) {
        if (max < counter.at(i)) {
            max = counter.at(i);
            maxType=i;
        }
    }
    // returns the index of the max.
    return maxType;
}
/**
 * Returns a strings vector contains the string representations of the classification of
 * each unclassified flower stored in the unclassifiedData, according to the given k value and desired distance.
 * The classification of each flower is determined using the k nearest neighbors algorithm.
 * @param k  the k value of the K nearest neighbors algorithm.
 * @param distance the distance to use the algorithm with.
 * @returnstrings vector contains the string representations of the classification of
 * each unclassified flower.
 */
vector<string> KNearestNeighbors::classifyData(int k,
                                               Geometry::Distance &distance,
                                               const vector<vector<Geometry::Point>> &classifiedData,
                            const vector<Geometry::Point> &unclassifiedData) {
    vector<string> classifyStrings;
    for (auto &modelPoint: unclassifiedData) {
        KNearestNeighbors KNN(modelPoint, classifiedData);
        int classification = KNN.classify(k, distance);
        if (classification == 0) {
            classifyStrings.emplace_back("Iris-setosa");
        } else if (classification == 1) {
            classifyStrings.emplace_back("Iris-versicolor");
        } else {
            // classification == 2
            classifyStrings.emplace_back("Iris-virginica");
        }
    }
    return classifyStrings;
}
void KNearestNeighbors::printNearestNeighbors(int K, Distance &distance) {
    vector<Point> neighbors= nearestNeighbors(K,distance);
    // uses the print implementation of Point to print all the points.
    for(const auto& item:neighbors){
        std::cout<< item ;
    }
    std::cout << endl;
}