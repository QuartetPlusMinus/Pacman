//
// Created by murt on 04.12.17.
//

#ifndef PACMAN_TILE_MAP_H
#define PACMAN_TILE_MAP_H

#include <SFML/Graphics.hpp>
#include <generated/service.pb.h>
#include <iostream>

const int HEIGHT_MAP = 18;
const int WIDTH_MAP = 23;

using namespace std;
using namespace pacman_service;

class TileMap {
public:
    explicit TileMap(StartReply *reply, sf::RenderWindow *window);

    int getHeight() {
        return height;
    }

    int getWidth() {
        return width;
    }

    void draw() {
        window->draw(mapSprite);
    }

private:
    sf::RenderWindow *window;
    sf::Texture texture;
    sf::Sprite mapSprite;

    int height;
    int width;
};


#endif //PACMAN_TILE_MAP_H
