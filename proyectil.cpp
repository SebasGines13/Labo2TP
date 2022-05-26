#include "proyectil.h"

///Constructor
proyectil::proyectil(sf::Vector2f posicion) {
    _sprProyectil = new sprite(13, 5, 1, sf::Vector2f(0, 0), .5f);
    _velDesplaz = 10.f;
    _velocidad = sf::Vector2f(0, 0);
    respawn(posicion);
}

sprite proyectil::getSprite()
{
    return *_sprProyectil;
}

void proyectil::setVelocidad(sf::Vector2f vel)
{
    _velocidad += vel;
}

void proyectil::update() {
    move(_velDesplaz, 0);
    animar();   
}

void proyectil::animar() {
    _sprProyectil->animarFrame();
}

void proyectil::respawn(sf::Vector2f posicion) {
    setPosition(posicion);
}

sf::FloatRect proyectil::getBounds()
{
    sf::FloatRect rect = sf::FloatRect(sf::Vector2f(getPosition().x, getPosition().y), sf::Vector2f(_sprProyectil->getFrameSize().x, _sprProyectil->getFrameSize().y));
    return rect;
}

void proyectil::draw(sf::RenderTarget& target, sf::RenderStates states) const
{  
    states.transform *= getTransform();
    target.draw(_sprProyectil->getSprite(), states);
}
