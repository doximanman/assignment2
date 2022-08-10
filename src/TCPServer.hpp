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
        const std::string _dataPath;
        int _sock;
    public:
        const int port;
        /**
         * opens the server.
         * @param port
         * @param dataPath path of the classified data.
         */
        TCPServer(int port,std::string dataPath);
        /**
         * handles the client. Sends, accepts and responds to messages.
         */
        void handleClient();
    };

} // Networking

#endif //SIMPLE_EXAMPLE_TCPSERVER_HPP
