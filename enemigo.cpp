#include "Enemigo.h"

///Constructor
Enemigo::Enemigo(sf::Vector2f posicion) {
    _sprite = new Sprite(15, 9, 4, sf::Vector2f(0, 0), .25f);
    _velDesplaz = 3.f;
    _velocidad = sf::Vector2f(0, 0);
    _direccion = (int)Direcciones::Left;
    _sprite->setFrameY(_direccion);
    respawn(posicion);
}

/// Gets

const Sprite& Enemigo::getSprite()
{
    return *_sprite;
}

sf::Vector2f Enemigo::getVelocidad()
{
    return _velocidad;
}

/// Sets
void Enemigo::setSentidoX(int frame) {
    _sprite->setFrameX(frame);
}

void Enemigo::setSentidoY(int frame) {
    _direccion = frame;
    _sprite->setFrameY(_direccion);
}

void Enemigo::setDireccion(int direccion)
{
    _direccion = direccion;
}

/// Métodos
void Enemigo::update() {
    _velocidad = {};
    srand(time(NULL));
    int aleatorio = rand() % 10;
    if (aleatorio > 7) {
        setSentidoY(rand() % 4);
    }

    if ( _direccion == (int)Direcciones::Left ) {
        _velocidad.x = -_velDesplaz;
    }
    else if ( _direccion == (int)Direcciones::Right ) {
        _velocidad.x = _velDesplaz;
    }
    else if (_direccion == (int)Direcciones::Up) {
        _velocidad.y = -_velDesplaz;
    }
    else if (_direccion == (int)Direcciones::Down) {
        _velocidad.y = _velDesplaz;
    }   
    move(_velocidad);
    _sprite->animar();
}

void Enemigo::respawn(sf::Vector2f posicion) {
    setPosition(posicion);
}

const sf::FloatRect Enemigo::getBounds()
{
    sf::FloatRect rect = sf::FloatRect(sf::Vector2f(getPosition().x, getPosition().y), sf::Vector2f(_sprite->getFrameSize().x, _sprite->getFrameSize().y));
    return rect;
}

void Enemigo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_sprite->getSprite(), states);
}
