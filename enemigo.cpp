#include "Enemigo.h"

Enemigo::Enemigo(sf::Vector2f posicion) {
    _sprMago = new Sprite(20, 16, 4, sf::Vector2f(9, 0), .1f);
    _sprMago->setPosicion(posicion);
}

Sprite Enemigo::getSprite() {
    return *_sprMago;
}


