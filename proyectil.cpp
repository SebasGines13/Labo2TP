#include "Proyectil.h"
#include <iostream>

///Constructor
Proyectil::Proyectil(sf::Vector2f posicion, Direcciones direccion) {
    _sprite = new Sprite(12, 5, 1, sf::Vector2f(0, 0), .25f);
    _velDesplaz = 6.f;
    _velocidad = sf::Vector2f(0, 0);
    respawn(posicion);
    _buffer.loadFromFile("audio/proyectil.wav");
    _sonido.setBuffer(_buffer);
    _sonido.setVolume(20.f);
    _sonido.setPitch(1.f);
    _sonido.play();
    _direccion = direccion;
    setOrigin(_sprite->getFrameSize().x / 2, _sprite->getFrameSize().y / 2);
}

Proyectil::~Proyectil()
{
    delete _sprite;
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
    switch (_direccion)
    {
    case Proyectil::Direcciones::Down:
        move(0, _velDesplaz);
        setRotation(90);
        break;
    case Proyectil::Direcciones::Left:
        move(-_velDesplaz, 0);
        setRotation(180);
        break;
    case Proyectil::Direcciones::Right:
        move(_velDesplaz, 0);
        break;
    case Proyectil::Direcciones::Up:
        move(0, -_velDesplaz);
        setRotation(-90);
        break;
    default:
        break;
    }
    _sprite->animar();   
}

void Proyectil::respawn(sf::Vector2f posicion) {
    setPosition(posicion);
}

void Proyectil::playSonido() {
    _sonido.play();
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
