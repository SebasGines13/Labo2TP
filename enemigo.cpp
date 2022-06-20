#include "Enemigo.h"
#include <iostream>
///Constructor
Enemigo::Enemigo(int sprClase, sf::Vector2f posicion) 
{
    if (sprClase == 11) {
        _sprite = new Sprite(sprClase, 9, 4, sf::Vector2f(0, 0), .25f);
        _velDesplaz = 3.f;
        _direccion = Direcciones::Left;
        _sprite->setFrameY((int)_direccion);
        spawn(posicion);
        _coolDown = 300;
    }
}

Enemigo::~Enemigo()
{
    delete _sprite;
}

/// Métodos
void Enemigo::update() {
    _velocidad = {};
    _coolDown--;
    if (_coolDown < 0) {
        Direcciones nuevaDireccion = (Direcciones)(rand() % 4);
        while (_direccion == nuevaDireccion){
            nuevaDireccion = (Direcciones)(rand() % 4);
        }
        setDireccion(nuevaDireccion);
        _coolDown = 300;
    } 

    if ( _direccion == Direcciones::Left ) {
        _velocidad.x = -_velDesplaz;
    }
    else if ( _direccion == Direcciones::Right ) {
        _velocidad.x = _velDesplaz;
    }
    else if (_direccion == Direcciones::Up) {
        _velocidad.y = -_velDesplaz;
    }
    else if (_direccion == Direcciones::Down) {
        _velocidad.y = _velDesplaz;
    }   
    move(_velocidad);
    _sprite->animar();
}

void Enemigo::spawn(sf::Vector2f posicion) {
    setPosition(posicion);
}


