#include "Personaje.h"

///sets
Personaje::Direcciones Personaje::getDireccion()
{
    return _direccion;
}

sf::Vector2f Personaje::getVelocidad()
{
    return _velocidad;
}

const Sprite& Personaje::getSprite()
{
    return *_sprite;
}

///Métodos
void Personaje::setSentidoX(int direccion) {
    _sprite->setFrameX(direccion);
}

void Personaje::setSentidoY(Direcciones direccion) {
    _sprite->setFrameY((int)direccion);
}

