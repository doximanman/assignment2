#include <iostream>
#include "Point.hpp"
#include "EuclideanDistance.hpp"
#include "ChebyshevDistance.hpp"
#include "ManhattanDistance.hpp"
#include "KNearestNeighbors.hpp"
#include <string>
#include "CSVManagement.hpp"
#include <fstream>

using namespace std;
using namespace Geometry;
using namespace CSV;

/**
 * Returns a strings vector contains the string representations of the classification of
 * each unclassified flower stored in the unclassifiedData, according to the given k value and desired distance.
 * The classification of each flower is determined using the k nearest neighbors algorithm.
 * @param k  the k value of the K nearest neighbors algorithm.
 * @param distance the distance to use the algorithm with.
 * @returnstrings vector contains the string representations of the classification of
 * each unclassified flower.
 */
vector<string> classifyData(int k, Geometry::Distance &distance, const vector<vector<Geometry::Point>> &classifiedData,
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


/**
 * Main entry point.s
 * Creates 3 csv files with the classifications of the unclassified flowers accepted,
 * one for each distance formula implemented.
 * @param argc
 * @param argv
 * @return int.
 */
int main(int argc, char *argv[]) {
    // create CSVManager object
    CSVManagement csvManagement("inputFiles/classified.csv",
                                "inputFiles/Unclassified.csv",
                                "outputFiles/");

    // create 3 types of distances
    EuclideanDistance euclideanDistance{};
    ManhattanDistance manhattanDistance{};
    ChebyshevDistance chebyshevDistance{};

    // creating classified oustput files
    csvManagement.createCSVOutputFile(classifyData(stoi(argv[1]), euclideanDistance,csvManagement.getClassifiedData(),csvManagement.getUnclassifiedData()),
                                      "euclidean_output.csv");
    csvManagement.createCSVOutputFile(classifyData(stoi(argv[1]), chebyshevDistance,
                                                   csvManagement.getClassifiedData(),
                                                   csvManagement.getUnclassifiedData()),
                                      "chebyshev_output.csv");
    csvManagement.createCSVOutputFile(classifyData(stoi(argv[1]), manhattanDistance,
                                                   csvManagement.getClassifiedData(),
                                                   csvManagement.getUnclassifiedData()),
                                      "manhattan_output.csv");
}
