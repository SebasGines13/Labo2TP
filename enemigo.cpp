#include "enemigo.h"

enemigo::enemigo(sf::Vector2f posicion) {
    _sprMago = new sprite(20, 16, 4, sf::Vector2f(9, 0), .1f);
    _sprMago->setPosicion(posicion);
}

sprite enemigo::getSprite() {
    return *_sprMago;
}


