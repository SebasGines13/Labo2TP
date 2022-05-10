#include "personaje.h"
#include <stdlib.h>
using namespace std;

///Constructor
personaje::personaje(int sprClase, int cantX, int cantY, Vector2i frameActual) {
    _sprPersonaje = new sprite(sprClase, cantX, cantY, frameActual);
    _velDesplaz = 0.15f;
    _velocidad = Vector2f(0, 0);
    _estado = Estados::QUIETO;
    _direccion = ABAJO;
}

///sets
void personaje::setPosicion(Vector2f position) {
    _sprPersonaje->setPosicion(position);
}

void personaje::setEstado(Estados estado) {
    _estado = estado;
}

void personaje::setVelocidad(Vector2f velocidad) {
    _velocidad = velocidad;
}

void personaje::setVelDesplaz(float velDesplaz) {
    _velDesplaz = velDesplaz;
}

void personaje::setDireccion(int direccion) {
    _direccion = direccion;
}

///gets
Vector2f personaje::getPosicion() {
    return _sprPersonaje->getPosicion();
}

sprite personaje::getSpritePersonaje() {
    return *_sprPersonaje;
}

Estados personaje::getCaminando() {
    return _estado;
}

Vector2f personaje::getVelocidad() {
    return _velocidad;
}

float personaje::getVelDesplaz() {
    return _velDesplaz;
}

int personaje::getDireccion() {
    return _direccion;
}

///Métodos
void personaje::setSentidoX(int frame) {
    _sprPersonaje->setFrameX(frame);
}

void personaje::setSentidoY(int frame) {
    _sprPersonaje->setFrameY(frame);
}

void personaje::mover(Vector2f movimiento) {
    _sprPersonaje->setPosicion(getPosicion() + movimiento);
}

void personaje::animar() {
    _sprPersonaje->animarFrame();
}

void personaje::update() {
    if (_estado==Estados::CAMINANDO) {
        seleccionarVelocidad();
        mover(_velocidad);
        animar();
    }
}

void personaje::seleccionarVelocidad() {
    switch (_direccion)
    {
    case ABAJO:
        _velocidad = Vector2f(0, _velDesplaz);
        setSentidoY(0);
        break;
    case IZQABAJO:
        _velocidad = Vector2f(-_velDesplaz, _velDesplaz);
        setSentidoY(0);
        break;
    case DERABAJO:
        _velocidad = Vector2f(_velDesplaz, _velDesplaz);
        setSentidoY(0);
        break;
    case IZQUIERDA:
        _velocidad = Vector2f(-_velDesplaz, 0);
        setSentidoY(1);
        break;
    case DERECHA:
        _velocidad = Vector2f(_velDesplaz, 0);
        setSentidoY(2);
        break;
    case ARRIBA:
        _velocidad = Vector2f(0, -_velDesplaz);
        setSentidoY(3);
        break;
    case IZQARRIBA:
        _velocidad = Vector2f(-_velDesplaz, -_velDesplaz);
        setSentidoY(3);
        break;
    case DERARRIBA:
        _velocidad = Vector2f(_velDesplaz, -_velDesplaz);
        setSentidoY(3);
        break;
    }
}