//
// Created by murt on 04.12.17.
//

#include "TileMap.h"

TileMap::TileMap(StartReply *reply, sf::RenderWindow *window) :
        window(window),
        height(HEIGHT_MAP + 2),
        width(WIDTH_MAP + 2) {

    sf::Image mapImage;
    mapImage.loadFromFile("src/map.png");

    sf::Image back;
    back.create(800, 640);

    for (unsigned int i = 0; i < width; i++) {
        back.copy(mapImage, 32 * i, 0, sf::IntRect(32, 64, 32, 32));
        back.copy(mapImage, 32 * i, 32 * (height - 1), sf::IntRect(32, 64, 32, 32));
    }

    for (unsigned int i = 0; i < height; i++) {
        back.copy(mapImage, 0, 32 * i, sf::IntRect(32, 64, 32, 32));
        back.copy(mapImage, 32 * (width - 1), 32 * i, sf::IntRect(32, 64, 32, 32));
    }

    std::string map_str;

    for (unsigned int i = 1; i < height - 1; i++) {
        map_str = reply->map(i - 1);
        for (unsigned int j = 1; j < width - 1; j++) {
            if (map_str[j - 1] != 's') {
                if (i == 1 && j == 1) { // top left corner
                    back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 3, 32 * 5, 32, 32));
                } else if (i == 1 && j == width - 2) { //top right corner
                    back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 5, 32 * 5, 32, 32));
                } else if (i == 1) { //top
                    back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 4, 32 * 5, 32, 32));
                } else if (i == height - 2 && j == 1) { // bottom left corner
                    back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 3, 32 * 7, 32, 32));
                } else if (i == height - 2 && j == width - 2) {
                    back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 5, 32 * 7, 32, 32));
                } else if (i == height - 2) { //bottom
                    back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 4, 32 * 7, 32, 32));
                } else if (j == 1) {
                    back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 3, 32 * 6, 32, 32));
                } else if (j == width - 2) {
                    back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 5, 32 * 6, 32, 32));
                }else if(map_str[j - 1] == '.') {
                    back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 4, 32 * 6, 32, 32));
                }
            } else {
                back.copy(mapImage, 32 * j, 32 * i, sf::IntRect(32 * 4, 32 * 3, 32, 32));
            }
        }
    }

    texture.loadFromImage(back);

    mapSprite.setTexture(texture, true);
    mapSprite.setPosition(0, 0);
}