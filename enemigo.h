#pragma once
#include "SFML/Graphics.hpp"
#include "sprite.h"
using namespace sf;

class enemigo {
private:
    sprite*     _sprMago;
    Texture     _txtMago;
public:
    enemigo(Vector2f posicion);
    sprite getSprite();
};

