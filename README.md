# TCP Server-Client Communication.
This project is coded in C++.

## Overview
This code uses server-client communication to classify points using the K Nearest Neighbors algorithm.

## Server
The server side uses TCP communication to accept and analyze messages from a client.
It is bound to a socket, and when told to handle a new client it listens to the client,
and gets messages from the client. The messages are assumed be a path to the input file.
It then classifies the points from the input file, and sends the client a message of the classifications.

## Client
The client side gets from the command line arguments a path to the input unclassified points, and a path to write the output classifications.
It starts by connecting to the server and sending it the path of the input file - a CSV file of unclassified points.
It then receives from the server the classifications of the points, and writes it to the output path.

## How we implemented it?
**TCPServer class**:
- Constructor of a port and a data path to a list of classified points (for the K Nearest Neighbors algorithm, we used K = 3).
- Function "void handleClient()" that simply listens to a new client and handles its messages accordingly.

**TCPClient class**:
- Constructor of a port, an ip address, a path of classified points (as mentioned above) and a path to save the classified points at.
- Function "void handleServer()" that connects to the server, receives the classification of the points as a string split by spaces (' '), then split them into a strings vector and creates a csv file with the corresponding classifications at the given output path.

## How to use?
In order to run the program, you should open two different terminals.

First, run the next command on one of the terminals:

```
g++ -std=c++11 src/*.cpp src/Server/Server.cpp
```

And then run the command: 

```
./a.out
```

On the same terminal.

Second, run the next command on the second terminal (while the first terminal is still running):

```
g++ -std=c++11 src/*.cpp src/Client/Client.cpp
```

Then the default command that will always work is:
```
./a.out inputFiles/Unclassified.csv outputFiles/classified.csv
```
But if you want to use different paths for the input (unclassified, first argument) and the output (classified, second argument), use this command instead:

```
./a.out X Y
```
Where X is the path to the input, and Y is the path to the output.
