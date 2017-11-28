//
// Created by viewsharp on 28.11.17.
//

#ifndef SERVER_GAMEOBJECT_H
#define SERVER_GAMEOBJECT_H

#include <string>

class GameObject {
public:
    GameObject() {}

    GameObject(int x, int y): x(x), y(y) {
    }
    int x;
    int y;
    std::string name;
protected:
    int id;
};

#endif //SERVER_GAMEOBJECT_H
