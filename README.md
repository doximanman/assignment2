# K Nearest Neighbors

This project is coded in C++.
## The Problem
We have a set of points (data), and each point belongs to some group (**Classified**).
Given a new point that is not classified, we need to decide which group that point should belong to.
There are different ways to do this, but one way is to use the **K Nearest Neighbors** algorithm.
## What is the K Nearest Neighbors Algorithm?
Given a group of classified points - our **data**, a number K - our **'accuracy'**, and a new point -  we need to classify that point.
This algorithm solves this problem by finding the K closest<sup>(1)</sup> points in the data from the point, and it decides the classification
of the point by the type that has the most points out of those K points.

<sup>(1)</sup> Closest is relative to a given distance function. In this algorithm we generalized it so that any distance function would work - and in our example we used 3 distances: Euclidian, Manhattan, and Chebyshev.

## Example
We have a set of points, lets say (1,1) (2,2) (3,3) (4,4) and (3.5,3.5), and they are classified:

group A: (1,1) , (2,2) , (3,3)

group B: (4,4) , (3.5,3.5)

And we are given the unclassified point (2.5,2.5), and 'accuracy' - K=3, and we need to classify the point.

Using Manhattan distance, the 3 closest points are : (2,2),(3,3),(3.5,3.5). 2 of those points belong to group A,
and 1 belongs to group B, so we conclude that the point should belong to group A.

## How we implemented it
**generic point class**:
- Can be of any dimension, with a given coordinates list.
- Can return any of its coordinates at will using the **at** function.

**abstract distance class**:
- Has an abstract distance function (not implemented).
- Whenever a distance function is needed in the code, an abstract refrence to the Distance class is used, to uphold generality.

**KNearestNeighbors class**:
- Constructed with a data table and a model point.
- Has 3 main functions:
- **distances(instance of Distance)**: returns a table of all the distances of the data points from the model point, given a distance function.

  **logic**: Simply creates a new table, iterates over the data table and inserts the distances of each point to the model point.
- **NearestNeighbors(integer K, instance of Distance)**: returns a list of the K nearest neighbors

  **logic**: Finds the closest point to the model point using the distances array k times, and ignores the previous minimums it found.
- **classify(integer K, instance of Distance)**: returns the classification of the point using the K nearest neighbors.

  **logic**: Simply uses the K nearest neighbors list and finds which type appears the most.

We also created extenders of the Distance class, specifically Euclidian distance, Manhattan distance, and Chebyshev distance.

**CSVManagement class**:
- Costructed with 3 strings representing the directories to classified.csv file, Unclassified.csv file and output folder respectively.
- Has 3 main functions:
- **createDataVector**: Returns a vector with the data stored in the csv file at the given path.

  **logic**: Opens the file in the given path, scan its lines and insert them into a string vector.
- **createClassifiedData**: Creates the classified data out of the given classified.csv file.

  **logic**: Scans the data table created by the classified.csv file line by line (using the function above) and inserts the coordinates of each line into a Points vector according to the Iris type name.
 - **createUnclassifiedData**:  Creates the unclassified data out of the given Unclassified.csv file.
 
   **logic**: Scans the data table created by the Unclassified.csv file line by line and inserst the coordinates of each line into a Points vecotr.
 - **createCSVOutputFile**: Writes the strings of a given string vector into a file named with the given fileOutputName. 
 
   **logic**: Opens a file with the give name, scans the lines of the given vector and writes it into the new file.

**main class**:
 - Contains 2 functions:
 - **classifyData**: Returns a strings vector contains the string classification representations of each unclassified Iris stored in the unclassifiedData, according to the given k value and desired distance.
 
   **logic**: Scans all the Points represrents the coordinates of each unclassified Iris. For each Point, we activate the K nearest neighbors algorithm with the given k value and distance fotmula desired in order to classify the Iris type. Finally, the function inserts each Iris string classification into a string vector (by the order they were scanned) and returns this vector at the end.
 - **main**: Creates 3 csv files with the classifications of the unclassified Irises accepted, one for each distance formula implemented: euclidean, chebyshev and manhattan distances.

## How to Use
choose some positive integer K, and run the commands (with the number instead of K):

```
g++ -std=c++11 src/*.cpp 
./a.out K
```

*euclidean_output.csv* which contains string classification representation of each unclassified Iris using the K nearest neighbors algorithm with the given K integer and using euclidean distance.

*chebyshev_output.csv* which contains string classification representation of each unclassified Iris using the K nearest neighbors algorithm with the given K integer and using chebyshev distance.

*manhattan_output.csv* which contains string classification representation of each unclassified Iris using the K nearest neighbors algorithm with the given K integer and using manhattan distance.
