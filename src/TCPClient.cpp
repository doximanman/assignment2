//
// Created by einat on 12/08/2022.
//

#include "TCPClient.hpp"
#include <string>
#include <utility>
#include "CSVManagement.hpp"
#include "Point.hpp"

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
        // convert buffer to type string
        string classifiedDataString(buffer);

        // add space at the end of the classifiedDataString in order to take care of all the characters in it
        classifiedDataString.push_back(' ');

        // classified string vector
        vector<string> classifiedData;

        // saves each current classification (split by space character ' ') into the vector
        string current{};
        for (char ch: classifiedDataString) {
            if (ch != ' ') {
                current.push_back(ch);
            } else {
                classifiedData.push_back(current);
                current = "";
            }
        }

        // create CSVManagement instance
        CSVManagement csvm(_classifiedDataPath, _unclassifiedDataPath);

        // save the classified data in the given classifiedData output path
        csvm.createCSVOutputFile(classifiedData, _classifiedDataPath);
    }
    close(_sock);
}

