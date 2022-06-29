#include "Personaje.h"

///Constructor
Personaje::Personaje() {
    _velocidad  = sf::Vector2f(0,0); 
    _velDesplaz = 0;
    _direccion  = Direcciones::Left;
    _coolDown   = 0; 
    _lastimado = false;
    _coolDownLastimado = 0;
    _velDesplaz = 0;
    _vida       = 0;
}

///sets
void Personaje::setDireccion(Direcciones direccion)
{
    _direccion = direccion;
    _sprite->setFrameY((int)direccion);
}

void Personaje::setLastimado(bool lastimado)
{
    _lastimado = lastimado;
}

void Personaje::setCoolDownLastimado(int coolDown)
{
    if (coolDown == -1) _coolDownLastimado--;
    else _coolDownLastimado = coolDown;
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

const float Personaje::getVelDesplaz()
{
    return _velDesplaz;
}

const Sprite& Personaje::getSprite()
{
    return *_sprite;
}

int Personaje::getVida()
{
    return _vida;
}

bool Personaje::getLastimado() 
{
    return _lastimado;
}

int Personaje::getCoolDownLastimado() 
{
    return _coolDownLastimado;
}

///M�todos
void Personaje::setSpriteQuieto() {
    _sprite->setFrameX(0);
}

void Personaje::spawn(sf::Vector2f posicion)
{
    setPosition(posicion);
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
