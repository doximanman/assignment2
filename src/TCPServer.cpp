//
// Created by kalo3 on 10-Aug-22.
//

#include "TCPServer.hpp"

#include <utility>
#include "KNearestNeighbors.hpp"
#include "CSVManagement.hpp"
#include "Point.hpp"
#include "EuclideanDistance.hpp"

using namespace std;
using namespace CSV;
using namespace Networking;
TCPServer::TCPServer(int port,string dataPath) : port(port),_dataPath(std::move(dataPath)){
    _sock=socket(AF_INET,SOCK_STREAM,0);
    if(_sock<0){
        perror("Error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr=INADDR_ANY;
    sin.sin_port=htons(this->port);
    if(bind(_sock,(struct sockaddr *)&sin,sizeof(sin))<0){
        perror("Error binding socket");
    }
    if(listen(_sock,5)<0){
        perror("Error listening to a socket");
    }
}

void TCPServer::handleClient() {
    // K of the K nearest neighbors algorithm.
    const int K=3;
    struct sockaddr_in client_sin;
    unsigned int addr_len=sizeof(client_sin);
    int client_sock=accept(_sock,(struct sockaddr*)&client_sin,&addr_len);
    if(client_sock<0){
        perror("Error accepting client");
    }
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int read_bytes = (int)recv(client_sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        cout << "Connection terminated" << endl;
        close(_sock);
        return;
    }
    else if (read_bytes < 0) {
        perror("Error reading client message");
    }
    else {
        // processing of client data.
        // client sends the server the input path.
        string inputPath(buffer);
        CSVManagement csvm(_dataPath,inputPath);
        vector<vector<Point>> data=csvm.getClassifiedData();
        EuclideanDistance euclideanDistance{};
        vector<string> classifiedData=KNearestNeighbors::classifyData(K,euclideanDistance,csvm.getClassifiedData(),csvm.getUnclassifiedData());
        string final;
        //combines the classified data into one string (with ' ' (space) as separation between classifications)
        for(int i=0;i<classifiedData.size();i++){
            if(i==0){
                final+=classifiedData.at(0);
            }
            else{
                final+=' '+classifiedData.at(i);
            }
        }

    }
    //sends combined string of the data point
    int sent_bytes =(int) send(client_sock, buffer, read_bytes, 0);
    if (sent_bytes < 0) {
        perror("Error sending to client");
    }
    close(_sock);
}