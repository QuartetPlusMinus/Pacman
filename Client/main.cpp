#include <string>
#include <iostream>

#include "PlayerConnectionClient.h"
#include "GameLoop.h"

using namespace std;

int main(int argc, char *argv[]) {

    string host;

    switch (argc) {
        case 1:
            cout << "Error: not found player name" << endl;
            return -1;
        case 2:
            host = "localhost";
            break;
        default:
            host = argv[2];
    }

    PlayerConnectionClient *connection;

    try {
        connection = new PlayerConnectionClient(grpc::CreateChannel(
                host + ":29563", grpc::InsecureChannelCredentials()));
        GameLoop game(connection, argv[1], host == "localhost");

    } catch (...) {
        cout << "Error: server not found" << endl;
    }
    return 0;
}