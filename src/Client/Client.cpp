#include "../TCPClient.hpp"

using namespace std;
using namespace Networking;

/**
 * Creates a TCP client, connect to the server and create csv output file in the given classified path directory.
 * @return int.
 */
int main(int argc,char* argv[]) {
    const int port = 12345;
    TCPClient client(argv[1], argv[2], port, "127.0.0.1");
    client.connectToServer();
}
