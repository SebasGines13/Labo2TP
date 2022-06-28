#include "Enemigo.h"
#include <iostream>
///Constructor
Enemigo::Enemigo(int sprClase, sf::Vector2f posicion) 
{
    _tipoEnemigo = sprClase;
    if (_tipoEnemigo == 1) {
        _sprite = new Sprite(11, 9, 4, sf::Vector2f(0, 0), .25f);
        _velDesplaz = 3.f;
        _direccion = Direcciones::Left;
        _sprite->setFrameY((int)_direccion);
        spawn(posicion);
        _coolDown = 300;
        _vida = 1;
    }
    else if (_tipoEnemigo == 2) {
        _sprite = new Sprite(11, 9, 4, sf::Vector2f(0, 0), .25f);
        _velDesplaz = 5.f;
        _direccion = Direcciones::Left;
        _sprite->setFrameY((int)_direccion);
        _sprite->setColor(sf::Color(0, 255, 0, 255));
        spawn(posicion);
        _coolDown = 250;
        _vida = 2;
    }
    else if (_tipoEnemigo == 3) {
        _sprite = new Sprite(13, 3, 4, sf::Vector2f(0, 0), .25f);
        _velDesplaz = 2.5f;
        _direccion = Direcciones::Left;
        _sprite->setFrameY((int)_direccion);
        spawn(posicion);
        _coolDown = 100;
        _vida = 5;
    }
}

///Destructor
Enemigo::~Enemigo()
{
    delete _sprite;
}

///Gets
int Enemigo::getTipoEnemigo()
{
    return _tipoEnemigo;
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

void Enemigo::recibirGolpe(int vida)
{
    _vida -= vida;
    colorSegunVida();
}

void Enemigo::colorSegunVida() {
    if (_vida > 0) {
        switch (_tipoEnemigo)
        {
        case 1:
            _sprite->setColor(sf::Color(255, 255, 255, 255));
            break;
        case 2:
            if(_vida ==1 ) _sprite->setColor(sf::Color(255, 0, 0, 255));
            break;
        case 3:
            _sprite->setColor(sf::Color(255, 51 * _vida, 51 * _vida, 255));
            break;
        }
    }
}
