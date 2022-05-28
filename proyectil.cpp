#include "Proyectil.h"

///Constructor
Proyectil::Proyectil(sf::Vector2f posicion) {
    _sprProyectil = new Sprite(13, 5, 1, sf::Vector2f(0, 0), .5f);
    _velDesplaz = 10.f;
    _velocidad = sf::Vector2f(0, 0);
    respawn(posicion);
}

Sprite Proyectil::getSprite()
{
    return *_sprProyectil;
}

void Proyectil::setVelocidad(sf::Vector2f vel)
{
    _velocidad += vel;
}

void Proyectil::update() {
    move(_velDesplaz, 0);
    animar();   
}

void Proyectil::animar() {
    _sprProyectil->animarFrame();
}

void Proyectil::respawn(sf::Vector2f posicion) {
    setPosition(posicion);
}

sf::FloatRect Proyectil::getBounds()
{
    sf::FloatRect rect = sf::FloatRect(sf::Vector2f(getPosition().x, getPosition().y), sf::Vector2f(_sprProyectil->getFrameSize().x, _sprProyectil->getFrameSize().y));
    return rect;
}

void Proyectil::draw(sf::RenderTarget& target, sf::RenderStates states) const
{  
    states.transform *= getTransform();
    target.draw(_sprProyectil->getSprite(), states);
}
