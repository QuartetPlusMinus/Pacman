#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#include <memory>
#include <string>

#include <grpc/support/log.h>
#include <thread>

#include "Player.h"
#include "../service.grpc.pb.h"

#include "PlayerConnectionClient.h"

using namespace pacman_service;

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML!");

    sf::CircleShape MyCircle(10);
    MyCircle.setFillColor(sf::Color::Red);

    sf::Texture t;
    t.loadFromFile("Client/src/pacimg.png");

    Player *player = new Player();
    player->sprite.setTexture(t);
    //player.setPosition(200, 200);

    PlayerConnectionClient playerConnection(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player->dir = LEFT;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player->dir = RIGHT;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player->dir = UP;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player->dir = DOWN;
        }

        GetCoordsReply reply = playerConnection.GetCoords();
        Coord position = reply.players(player->id()).coords();
        player->sprite.setPosition(position.x(), position.y());

        window.clear();
        window.draw(player->sprite);
        window.display();

        usleep(16777);
    }

    return 0;
}
