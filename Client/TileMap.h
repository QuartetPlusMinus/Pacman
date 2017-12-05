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
    explicit TileMap(StartReply *reply, sf::RenderWindow *window) :
            window(window),
            height(HEIGHT_MAP + 2),
            width(WIDTH_MAP + 2) {

        sf::Image mapImage;
        mapImage.loadFromFile("src/map.png");

        sf::Image back;
        back.create(800, 640);

        for (unsigned int i = 0; i < width; i++) {
            back.copy(mapImage, 32*i, 0, sf::IntRect(32, 64, 32, 32));
            back.copy(mapImage, 32*i, 32 * (height-1), sf::IntRect(32, 64, 32, 32));
        }

        for (unsigned int i = 0; i < height; i++) {
            back.copy(mapImage, 0, 32 * i, sf::IntRect(32, 64, 32, 32));
            back.copy(mapImage, 32 * (width - 1), 32 * i, sf::IntRect(32, 64, 32, 32));
        }

        std::string map_str;

        for (unsigned int i = 1; i < height - 1; i++) {
            map_str = reply->map(i-1);
            for (unsigned int j = 1; j < width - 1; j++) {
                switch (map_str[j-1]) {
                    case '.':
                        back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 4, 32 * 6, 32, 32));
                        break;
                    case 's':
                        back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 17, 32 * 3, 32, 32));
                        break;
                    case 'T':
                        back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 3, 32 * 5, 32, 32));
                        break;
                    case 't':
                        back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32*5, 32*5, 32, 32));
                        break;
                    case 'B':
                        back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 3, 32 * 7, 32, 32));
                        break;
                    case 'b':
                        back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 5, 32 * 7, 32, 32));
                        break;
                    default:
                        break;
                }
            }
        }

        texture.loadFromImage(back);

        mapSprite.setTexture(texture, true);
        mapSprite.setPosition(0, 0);
    }

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