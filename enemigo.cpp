#include "Enemigo.h"
#include <iostream>
///Constructor
Enemigo::Enemigo(int tipoEnemigo, sf::Vector2f posicion, int dificultad, const int &coolDownLastimado) 
{
    _tipoEnemigo = tipoEnemigo;
    _vida = tipoEnemigo;
    _velDesplaz = 2.f + (dificultad * tipoEnemigo * 0.25f);
    _coolDown = 80 + (dificultad * tipoEnemigo * 5);
    _coolDownInicialDireccion = _coolDown;
    _coolDownLastimado = coolDownLastimado;
    _lastimado = false;
    if (_tipoEnemigo == 1) {
        _sprite = new Sprite(11, 9, 4, sf::Vector2f(0, 0), .25f);
    }
    else if (_tipoEnemigo == 2) {
        //_sprite = new Sprite(111, 9, 4, sf::Vector2f(0, 0), .25f);
        //_sprite->setColor(sf::Color(0, 255, 0, 255));
        _sprite = new Sprite(112, 3, 4, sf::Vector2f(0, 0), .15f);
    }
    else if (_tipoEnemigo == 3) {
        _sprite = new Sprite(13, 3, 4, sf::Vector2f(0, 0), .25f);
        _vida += 2; // al ser el jefe, le sumo más vida.
    }
    else if (_tipoEnemigo == 4) {
        _sprite = new Sprite(14, 3, 4, sf::Vector2f(0, 0), .25f);
        _vida += 2; // al ser el jefe, le sumo más vida.
    }
    else if (_tipoEnemigo == 5) {
        _sprite = new Sprite(15, 3, 4, sf::Vector2f(0, 0), .25f);
        _vida += 2; // al ser el jefe, le sumo más vida.
    }
    else if (_tipoEnemigo == 6) {
        _sprite = new Sprite(16, 3, 4, sf::Vector2f(0, 0), .25f);
        _vida += 2; // al ser el jefe, le sumo más vida.
    }
    _direccion = Direcciones::Left;
    _sprite->setFrameY((int)_direccion);
    spawn(posicion);
}

///Destructor
Enemigo::~Enemigo()
{
    delete _sprite;
}

///Gets
int Enemigo::getTipoEnemigo()
{
    if (_tipoEnemigo > 2) return _tipoEnemigo * 5;
    else return _tipoEnemigo;
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
        _coolDown = _coolDownInicialDireccion;
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
    colorSegunVida();
}

void Enemigo::recibirGolpe(int vida)
{
    _vida -= vida;
    _lastimado = true;
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
            if(_vida == 1) _sprite->setColor(sf::Color(255, 0, 0, 255));
            break;
        default:
            _sprite->setColor(sf::Color(255, 255/(_tipoEnemigo+2) * _vida, 255/(_tipoEnemigo+2) * _vida, 255));
            break;
        }
    }
}
