//
// Created by einat on 02/08/2022.
//

#ifndef ASSIGNMENT1_CSVMANAGEMENT_HPP
#define ASSIGNMENT1_CSVMANAGEMENT_HPP

#include "Distance.hpp"

namespace CSV {
    class CSVManagement {
    private:

        /**
         * classifiedData vector
         */
        vector<vector<Geometry::Point>> _classifiedData;

        /**
         * unclassifiedData vector
         */
        vector<Geometry::Point> _unclassifiedData;

        /**
         * path to classified.csv
         */
        string _classifiedDataPath;

        /**
         * path to Unclassified.csv
         */
        string _unclassifiedDataPath;

        /**
         * path to output csv files
         */
        string _fileOutputPath;

        /**
         * Returns a vector with the data stored in the csv file at the given path.
         * @param filePath the path to the input file.
         * @return a vector with the data stored in the csv file at the given path.
         */
        vector<vector<string>> createDataVector(const string &filePath);

        /**
         * Creates the classified data out of the given classified.csv file.
         */
        void createClassifiedData();

        /**
         * Creates the unclassified data out of the given Unclassified.csv file.
         */
        void createUnclassifiedData();

    public:

        /**
         * Getter of the classified data.
         * @return classifiedData.
         */
        vector<vector<Geometry::Point>> getClassifiedData();

        /**
         * Getter of unclassified data.
         * @return unclassifiedData.
         */
        vector<Geometry::Point> getUnclassifiedData();

        /**
         * Writes the strings of the given string vector into a file named with the given fileOutputPath.
         * @param classifiedData strings vector.
         * @param fileOutputPath the path of the output file.
         */
        static void createCSVOutputFile(const vector<string> &classifiedData, const string &fileOutputPath);

        /**
         * Constructor.
         * @param classifiedDataPath path to classified.csv.
         * @param unclassifiedDataPath path to Unclassified.csv
         */
        CSVManagement(const string &classifiedDataPath, const string &unclassifiedDataPath);
    };
}
#endif //ASSIGNMENT1_CSVMANAGEMENT_HPP

