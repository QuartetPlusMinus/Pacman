#include <iostream>
#include <SFML/Graphics.hpp>

#include "PlayerConnectionClient.h"
#include "service.grpc.pb.h"
#include "GameLoop.h"

using namespace std;

int main (int argc, char *argv[]) {

    if (argc < 2) {
        cout<<"not found player name"<<endl;
        return -1;
    }


    PlayerConnectionClient connection(grpc::CreateChannel(
            "localhost:29563", grpc::InsecureChannelCredentials()));

//    ConnectRequest request;
//    while (true) {
//        ConnectReply reply = connection.Connect(request);
//        usleep(200000);
//    }
    GameLoop game(&connection, argv[1]);

    return 0;
}