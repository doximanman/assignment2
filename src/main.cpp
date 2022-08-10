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
                                "inputFiles/Unclassified.csv");

    // create 3 types of distances
    EuclideanDistance euclideanDistance{};
    ManhattanDistance manhattanDistance{};
    ChebyshevDistance chebyshevDistance{};

    // creating classified output files
    csvManagement.createCSVOutputFile(KNearestNeighbors::classifyData(stoi(argv[1]), euclideanDistance,csvManagement.getClassifiedData(),csvManagement.getUnclassifiedData()),
                                      "outputFiles/euclidean_output.csv");
    csvManagement.createCSVOutputFile(KNearestNeighbors::classifyData(stoi(argv[1]), chebyshevDistance,
                                                   csvManagement.getClassifiedData(),
                                                   csvManagement.getUnclassifiedData()),
                                      "outputFiles/chebyshev_output.csv");
    csvManagement.createCSVOutputFile(KNearestNeighbors::classifyData(stoi(argv[1]), manhattanDistance,
                                                   csvManagement.getClassifiedData(),
                                                   csvManagement.getUnclassifiedData()),
                                      "outputFiles/manhattan_output.csv");
}
