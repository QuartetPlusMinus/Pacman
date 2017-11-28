//
// Created by viewsharp on 28.11.17.
//

#ifndef SERVER_MOVINGGAMEOBJECT_H
#define SERVER_MOVINGGAMEOBJECT_H

#include "GameObject.h"

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class MovingGameObject: public GameObject {
public:
    MovingGameObject() {}

    MovingGameObject(int x, int y, Direction dir): GameObject(x,y), dir(dir), speed(1){}

    void step() {
        switch (dir) {
            case UP:
                y -= speed;
                break;

            case RIGHT:
                x += speed;
                break;

            case DOWN:
                y += speed;
                break;

            case LEFT:
                x -= speed;
                break;
        }
    }
    Direction dir;
protected:
    int speed;
};


#endif //SERVER_MOVINGGAMEOBJECT_H
