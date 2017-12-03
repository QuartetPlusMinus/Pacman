#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "PlayerConnectionClient.h"
#include "service.grpc.pb.h"
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
        case 3:
            host = argv[2];
            break;
    }

    PlayerConnectionClient *connection;

    try {
        connection = new PlayerConnectionClient(grpc::CreateChannel(
                host + ":29563", grpc::InsecureChannelCredentials()));

    } catch (...) {
        cout << "Error: server not found" << endl;
    }


    GameLoop game(connection, argv[1]);

    return 0;
}