#pragma once
#include "SFML/Graphics.hpp"
#include "Sprite.h"

class Enemigo {
private:
    Sprite*      _sprMago;
    sf::Texture  _txtMago;
public:
    Enemigo(sf::Vector2f posicion);
    Sprite getSprite();
};

