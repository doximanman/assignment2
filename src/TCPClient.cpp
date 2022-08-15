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
        port(port), _ip_address(ip_adress),
        _unclassifiedDataPath(std::move(unclassifiedDataPath)),
        _classifiedDataPath(std::move(classifiedDataPath)) {
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin{AF_INET,htons(this->port),inet_addr(_ip_address)};

    if (connect(_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }
}

void TCPClient::connectToServer() {
    char data_addr[4096]={0};
    int data_len=sizeof(data_addr);
    std::strcpy(data_addr, _unclassifiedDataPath.c_str());
    int sent_bytes = (int)send(_sock, data_addr, data_len, 0);

    if (sent_bytes < 0) {
        cout << "Error sending the data to the serve" << endl;
    }

    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int read_bytes = (int)recv(_sock, buffer, expected_data_len, 0);
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
        for (char &ch: classifiedDataString) {
            if (ch != ' ') {
                current.push_back(ch);
            } else {
                classifiedData.push_back(current);
                current = "";
            }
        }
        // save the classified data in the given classifiedData output path
        CSVManagement::createCSVOutputFile(classifiedData, _classifiedDataPath);
    }
    close(_sock);
}


