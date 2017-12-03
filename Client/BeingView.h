//
// Created by viewsharp on 02.12.17.
//

#ifndef PACMAN_BEINGVIEW_H
#define PACMAN_BEINGVIEW_H

#include "service.grpc.pb.h"
#include "SFML/Graphics.hpp"
#include <string>

using namespace pacman_service;
using namespace std;

class BeingView: public Being {

public:
    BeingView(Being data, string imgPath):
            Being(data),
            s(new sf::Sprite)
    {
        sf::Texture texture;
        texture.loadFromFile(imgPath);
        s->setTexture(texture);
    }

    void setData(const Being &data) {
        clear_pos();
        auto *pos = new Point();
        pos->set_x(data.pos().x());
        pos->set_y(data.pos().y());
        set_allocated_pos(pos);
        set_status(data.status());
        set_direction(data.direction());
    }

    sf::Sprite *getSprite() {
        s->setPosition(pos().x(), pos().y());
        return s;
    }

private:
    sf::Sprite *s;

};

#endif //PACMAN_BEINGVIEW_H