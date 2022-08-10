#include "TCPServer.hpp"

using namespace std;
using namespace Networking;

/**
 * Creates a TCP server and a client
 * @param argc
 * @param argv
 * @return int.
 */
int main(int argc, char *argv[]) {
    const int port=12345;
    const string dataPath="../inputFiles/classified";
    TCPServer server(12345,dataPath);
    server.handleClient();
    // needs client implementation here.
}
