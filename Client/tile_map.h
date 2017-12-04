//
// Created by murt on 04.12.17.
//

#ifndef PACMAN_TILE_MAP_H
#define PACMAN_TILE_MAP_H

#include <SFML/Graphics.hpp>
#include <generated/service.pb.h>

const int HEIGHT_MAP = 18;
const int WIDTH_MAP = 23;

using namespace pacman_service;

class TileMap {
public:
    explicit TileMap(StartReply *reply, sf::RenderWindow *window):
            window(window){
        height = HEIGHT_MAP + 2;
        width = WIDTH_MAP + 2;
       // map = map_representation;
        sf::Image map_image;
        map_image.loadFromFile("src/map.png");
        map_texture.loadFromImage(map_image);
        generate_map(reply);
    }


    void generate_map(StartReply* reply) {
        window->clear();
        sf::Sprite buf;
        buf.setTexture(map_texture);
        for (int i = 0; i < width; i++) {
            buf.setTextureRect(sf::IntRect(32, 64, 32, 32));
            buf.setPosition(32 * i, 0);
            window->draw(buf);
            buf.setTextureRect(sf::IntRect(32, 64, 32, 32));
            buf.setPosition(32*i, width - 1);
            window->draw(buf);
        }

        for (int i = 0; i < height; i++) {
            buf.setTextureRect(sf::IntRect(32, 64, 32, 32));
            buf.setPosition(0, 32 * i);
            window->draw(buf);
            buf.setTextureRect(sf::IntRect(32, 64, 32, 32));
            buf.setPosition(height - 1, 32 * i);
            window->draw(buf);
        }
        std::string map_str;
        for (int i = 1; i < height - 1; i++) {
            //tiles[i] = new sf::Sprite;
            map_str = reply->map(i);
            for (int j = 1; j < width - 1; j++) {
              //  tiles[i][j].setTexture(map_texture);
                if (map_str[j] == '.') buf.setTextureRect(sf::IntRect(32 * 4, 32 * 6, 32, 32));
                if (map_str[j] == 's') buf.setTextureRect(sf::IntRect(32 * 17, 32 * 3, 32, 32));
//                if (map[i][j] == '1')bufj].setTextureRect(sf::IntRect(32, 64, 32, 32));
                if (map_str[j] == 'B') buf.setTextureRect(sf::IntRect(32 * 3, 32 * 7, 32, 32));
                if (map_str[j] == 'b') buf.setTextureRect(sf::IntRect(32 * 5, 32 * 7, 32, 32));
                if (map_str[j] == 'T') buf.setTextureRect(sf::IntRect(32 * 3, 32 * 5, 32, 32));
                if (map_str[j] == 't') buf.setTextureRect(sf::IntRect(32 * 5, 32 * 5, 32, 32));
                buf.setPosition(j * 32, i * 32);
                window->draw(buf);
            }
        }
        window->display();
        sf::Texture texture;
        texture.loadFromImage(window->capture());
        map_s.setTexture(texture, true);
        map_s.setPosition(0,0);
    }
    int getHeight() {
        return height;
    }

    int getWidth() {
        return width;
    }

    sf::Sprite map_s;

private:
    sf::RenderWindow *window;
    sf::Texture map_texture;
    int height;
    int width;

};


#endif //PACMAN_TILE_MAP_H
