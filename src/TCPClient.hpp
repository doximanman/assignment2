//
// Created by einat on 12/08/2022.
//

#ifndef SIMPLE_EXAMPLE_TCPCLIENT_HPP
#define SIMPLE_EXAMPLE_TCPCLIENT_HPP

#include <iostream>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

namespace Networking {
    class TCPClient {
    private:
        /**
         * Path to the unclassified data.
         */
        const std::string _unclassifiedDataPath;

        /**
         * Path to the classified data.
         */
        const std::string _classifiedDataPath;

        /**
         * Socket number.
         */
        int _sock;

        /**
         * IP adress number.
         */
        const char *_ip_address;
    public:
        /**
         * Port number.
         */
        const int port;

        /**
         * Constructor of a new Client.
         * @param unclassifiedDataPath string.
         * @param classifiedDataPath string.
         * @param port number.
         */
        TCPClient(std::string unclassifiedDataPath, std::string classifiedDataPath, int port, const char *ip_adress);

        /**
         * Connects the server and send it the unclassifiedDataPath;
         */
        void connectToServer();
    };
}
#endif //SIMPLE_EXAMPLE_TCPCLIENT_HPP
