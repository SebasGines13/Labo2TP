#include "Personaje.h"

///Constructor
Personaje::Personaje() {
    _velocidad  = sf::Vector2f(0,0); 
    _velDesplaz = 1.f;
    _direccion  = Direcciones::Left;
    _coolDown   = 100; 
    _velDesplaz = 3.f;
}

///sets
void Personaje::setDireccion(Direcciones direccion)
{
    _direccion = direccion;
    _sprite->setFrameY((int)direccion);
}

///gets
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
void Personaje::setSpriteQuieto() {
    _sprite->setFrameX(0);
}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_sprite->getSprite(), states);
}

const sf::FloatRect Personaje::getBounds()
{
    sf::FloatRect rect = sf::FloatRect(sf::Vector2f(getPosition().x, getPosition().y), sf::Vector2f(_sprite->getFrameSize().x, _sprite->getFrameSize().y));
    return rect;
}
