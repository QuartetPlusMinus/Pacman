//
// Created by viewsharp on 01.12.17.
//

#ifndef ONENIGHTPACMAN_PLAYER_H
#define ONENIGHTPACMAN_PLAYER_H

#include "BeingView.h"
#include <string>

using namespace pacman_service;
using namespace std;

class Pacman : public BeingView {

public:

    Pacman(const string &name, const Being &data):
            BeingView(data, 320, 0){
        this->name = name;
    }

    string name;

private:

};

class Health {

public:
    explicit Health():
            imgX(0),
            imgY(608),
            sprite(new sf::Sprite)
    {
        sf::Image img;
        img.loadFromFile("src/heart.png");
        img.createMaskFromColor(sf::Color::Black);
        texture = new sf::Texture;
        texture->loadFromImage(img);
        sprite->setTexture(*texture);
    }
    ~Health() {
        delete texture;
        delete sprite;
    }

    void setPos(int x, int y) {
        imgX = x;
        imgY = y;
    };
    int getImgY() {
        return imgY;
    }
    int getImgX() {
        return imgX;
    }

    sf::Sprite *getSprite();

private:
    sf::Sprite *sprite;
    sf::Texture *texture;
    int imgX;
    int imgY;
};

#endif //ONENIGHTPACMAN_PLAYER_H
