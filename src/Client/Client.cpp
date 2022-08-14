#include "../TCPClient.hpp"

using namespace std;
using namespace Networking;

/**
 * Creates a TCP client, connect to the server and create csv output file in the given classified path directory.
 * @return int.
 */
int main() {
    const int port = 12345;
    const string outputDataPath = "../outputFiles/classified.csv";
    const string inputDataPath = "../inputFiles/Unclassified.csv";
    TCPClient client(inputDataPath, outputDataPath, port, "127.0.0.1");
    client.handleServer();
}
