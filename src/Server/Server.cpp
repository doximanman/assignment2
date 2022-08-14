#include "../TCPServer.hpp"

using namespace std;
using namespace Networking;

/**
 * Creates a TCP server, and starts listening for a client.
 * @return int.
 */
int main() {
    const int port = 12345;
    const string dataPath = "../inputFiles/classified.csv";
    TCPServer server(port, dataPath);
    server.handleClient();
}
