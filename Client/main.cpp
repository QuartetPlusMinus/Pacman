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

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML!");

    sf::CircleShape MyCircle(10);
    MyCircle.setFillColor(sf::Color::Red);

    sf::Texture pacTexture;
    pacTexture.loadFromFile("src/pacimg.png");

    sf::Texture ghostTexture;
    ghostTexture.loadFromFile("src/ghost.png");

    PlayerConnectionClient connection(grpc::CreateChannel(
            "localhost:29563", grpc::InsecureChannelCredentials()));

//    ConnectRequest request;
//    while (true) {
//        ConnectReply reply = connection.Connect(request);
//        usleep(200000);
//    }
    GameLoop game(&window, &connection, argv[1]);

    return 0;
}