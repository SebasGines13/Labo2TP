#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class enemigo {
private:
    Texture txtMonster;
    Sprite sprMonster;
public:
    enemigo(Vector2f posicion);
    Sprite getSprite();
};

