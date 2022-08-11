# TCP Server-Client Communication.
This project is coded in C++.

## Overview
This code uses server-client communication to classify points using the K Nearest Neighbors algorithm.

## Server
The server side uses TCP communication to accept and analyze messages from a client.
It is bound to a socket, and when told to handle a new client it listens to the client,
and gets messages from the client. The messages are assumed be a path to the input file.
It then classifies the points from the input file, and sends the client a message of the classifications.

## Client (not yet implemented)
The client side gets from the command line arguments a path to the input unclassified points, and a path to write the output classifications.
It starts by connecting to the server and sending it the path of the input file - a CSV file of unclassified points.
It then receives from the server the classifications of the points, and writes it to the output path.

## How we implemented it
**TCPServer class**:
- Constructor of a port and a data path to a list of classified points (for the K Nearest Neighbors algorithm).
- Function "void handleClient()" that simply listens to a new client and handles its messages accordingly.

Client class yet to be implemented.
