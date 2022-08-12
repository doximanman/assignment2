//
// Created by kalo3 on 10-Aug-22.
//

#ifndef SIMPLE_EXAMPLE_TCPSERVER_HPP
#define SIMPLE_EXAMPLE_TCPSERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

namespace Networking {
    /**
     * A TCP server that gets classified and unclassified files from a client and classifies them
     * according to the K Nearest Neighbors algorithm.
     */
    class TCPServer {
    private:
        //path to the csv file that stores the classified data.
        const std::string _dataPath;
        //socket
        int _sock;
    public:
        const int port;
        /**
         * Opens the server.
         * @param port.
         * @param dataPath path to the csv file that stores the classified data.
         */
        TCPServer(int port,std::string dataPath);
        /**
         * Starts listening for a client.
         */
        void handleClient();
    };

} // Networking

#endif //SIMPLE_EXAMPLE_TCPSERVER_HPP
