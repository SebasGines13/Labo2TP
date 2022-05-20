#pragma once
#include "SFML/Graphics.hpp"
#include "sprite.h"

class enemigo {
private:
    sprite*      _sprMago;
    sf::Texture  _txtMago;
public:
    enemigo(sf::Vector2f posicion);
    sprite getSprite();
};

