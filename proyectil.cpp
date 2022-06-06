#include "Proyectil.h"

///Constructor
Proyectil::Proyectil(sf::Vector2f posicion) {
    _sprite = new Sprite(12, 5, 1, sf::Vector2f(0, 0), .25f);
    _velDesplaz = 6.f;
    _velocidad = sf::Vector2f(0, 0);
    respawn(posicion);
}

Sprite Proyectil::getSprite()
{
    return *_sprite;
}

void Proyectil::setVelocidad(sf::Vector2f vel)
{
    _velocidad += vel;
}

void Proyectil::update() {
    move(_velDesplaz, 0);
    _sprite->animar();   
}

void Proyectil::respawn(sf::Vector2f posicion) {
    setPosition(posicion);
}

const sf::FloatRect Proyectil::getBounds()
{
    sf::FloatRect rect = sf::FloatRect(sf::Vector2f(getPosition().x, getPosition().y), sf::Vector2f(_sprite->getFrameSize().x, _sprite->getFrameSize().y));
    return rect;
}

void Proyectil::draw(sf::RenderTarget& target, sf::RenderStates states) const
{  
    states.transform *= getTransform();
    target.draw(_sprite->getSprite(), states);
}
