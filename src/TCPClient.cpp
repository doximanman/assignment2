//
// Created by einat on 12/08/2022.
//

#include "TCPClient.hpp"
#include "TCPServer.hpp"
#include <string>
#include <utility>
#include "KNearestNeighbors.hpp"
#include "CSVManagement.hpp"
#include "Point.hpp"
#include "EuclideanDistance.hpp"

using namespace std;
using namespace CSV;
using namespace Networking;

TCPClient::TCPClient(std::string unclassifiedDataPath, std::string classifiedDataPath, int port, const char *ip_adress)
        :
        port(port), _ip_address(std::move(ip_adress)),
        _unclassifiedDataPath(std::move(unclassifiedDataPath)),
        _classifiedDataPath(std::move(classifiedDataPath)) {
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(_ip_address);
    sin.sin_port = htons(this->port);

    if (connect(_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }
}

void TCPClient::handleServer() {
    int data_len = static_cast<int>(_unclassifiedDataPath.length());
    char data_addr[data_len];
    std::strcpy(data_addr, _unclassifiedDataPath.c_str());
    int sent_bytes = send(_sock, data_addr, data_len, 0);

    if (sent_bytes < 0) {
        perror("Error sending the data to the serve");
    }

    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(_sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        cout << "Connection terminated" << endl;
        close(_sock);
        return;
    } else if (read_bytes < 0) {
        perror("Error reading client message");
    } else {
        vector<string> classifiedData;
        string current{};
        for (int i = 0; i < expected_data_len; i++) {
            if (buffer[i] != ' ') {
                //current.append(buffer[i]);
            }
        }
    }

    close(_sock);
}

