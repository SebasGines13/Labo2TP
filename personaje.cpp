#include "personaje.h"
#include <stdlib.h>
using namespace std;

///Constructor
personaje::personaje(int sprClase, int cantX, int cantY, Vector2f frameActual, juegoProyectil& juego)
    : _juego(juego)
{
    _sprPersonaje = new sprite(sprClase, cantX, cantY, frameActual, .1f);
    _velDesplaz = 3.5f;
    _velocidad = Vector2f(0, 0);
    _estado = Estados::QUIETO;
    _direccion = ABAJO;
    _buffer.loadFromFile("audio/paso.wav");
    _pasos.setBuffer(_buffer);
    _pasos.setVolume(10.f);
    _pasos.setPitch(1.f);
    _coolDown = 5;
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

void personaje::setCoolDown(unsigned int coolDown){
    _coolDown = coolDown;
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

juegoProyectil& personaje::getJuegoActual(){
    return _juego;
}

unsigned int personaje::getCoolDown()
{
    return _coolDown;
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

void personaje::update(Vector2f velocidad) {
    if (_estado == Estados::CAMINANDO) {
        actualizaVelocidad(velocidad);
        mover(_velocidad);
        animar();
        if (_pasos.getStatus() != _pasos.Playing) { // si no está sonando ya los pasos, se inicia el sonido
            _pasos.play(); // sonido de pasos
        }
    }
    else if(_estado == Estados::QUIETO) {
        _pasos.stop(); // para de sonar los pasos, porque está quieto
    }
}

void personaje::actualizaVelocidad(Vector2f velocidad) {
    _velocidad = velocidad;
    switch (_direccion)
    {
    case ABAJO:
        setSentidoY(ABAJO);
        break;
    case IZQABAJO:
        setSentidoY(ABAJO);
        break;
    case DERABAJO:
        setSentidoY(ABAJO);
        break;
    case IZQUIERDA:
        setSentidoY(IZQUIERDA);
        break;
    case DERECHA:
        setSentidoY(DERECHA);
        break;
    case ARRIBA:
        setSentidoY(ARRIBA);
        break;
    case IZQARRIBA:
        setSentidoY(ARRIBA);
        break;
    case DERARRIBA:
        setSentidoY(ARRIBA);
        break;
    }
}

void personaje::disparar()
{
    getJuegoActual().crearProyectil(getPosicion());
    _coolDown = 7;
}
