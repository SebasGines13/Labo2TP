#include "personaje.h"

///Constructor
personaje::personaje(int sprClase, int cantX, int cantY, sf::Vector2f frameActual, juegoProyectil& juego, Controller& controller)
    : _juego(juego), _controller(controller)
{
    _sprPersonaje = new sprite(sprClase, cantX, cantY, frameActual, .1f);
    _velDesplaz = 3.5f;
    _velocidad = sf::Vector2f(0, 0);
    _estado = (unsigned int)Estados::Quieto;
    _direccion = (unsigned int)Direcciones::Down;
    _buffer.loadFromFile("audio/paso.wav");
    _pasos.setBuffer(_buffer);
    _pasos.setVolume(10.f);
    _pasos.setPitch(1.f);
    _coolDown = 5;
    move(200.f, 200.f);
}

///sets
void personaje::setVelDesplaz(float velDesplaz) {
    _velDesplaz = velDesplaz;
}

///gets
sprite personaje::getSpritePersonaje(){
    return *_sprPersonaje;
}

float personaje::getVelDesplaz(){
    return _velDesplaz;
}

unsigned int  personaje::getDireccion(){
    return _direccion;
}

juegoProyectil& personaje::getJuegoActual(){
    return _juego;
}


///Métodos
void personaje::setSentidoX(int frame) {
    _sprPersonaje->setFrameX(frame);
}

void personaje::setSentidoY(int frame) {
    _sprPersonaje->setFrameY(frame);
}

void personaje::animar() {
    _sprPersonaje->animarFrame();
}

void personaje::update() {
    ///Chequeo las teclas
    _estado = (unsigned int)Estados::Quieto; // inicio con el jugador asumiéndolo como que no está caminando.
    if (_controller.isPressed(Controller::Buttons::Left)) {
        _estado = (unsigned int)Estados::Caminando; // jugador comienza a caminar
        _direccion = (unsigned int)Direcciones::Left;
        _sprPersonaje->setFrameY(_direccion);
        move(-_velDesplaz, 0);
    }
    if (_controller.isPressed(Controller::Buttons::Right)) {
        _estado = (unsigned int)Estados::Caminando; // jugador comienza a caminar
        _direccion = (unsigned int)Direcciones::Right;
        _sprPersonaje->setFrameY(_direccion);
        move(_velDesplaz, 0);
    }
    if (_controller.isPressed(Controller::Buttons::Up)) {
        _estado = (unsigned int)Estados::Caminando; // jugador comienza a caminar
        _direccion = (unsigned int)Direcciones::Up;
        _sprPersonaje->setFrameY(_direccion);
        move(0, -_velDesplaz);
    }
    if (_controller.isPressed(Controller::Buttons::Down)) {
        _estado = (unsigned int)Estados::Caminando; // jugador comienza a caminar
        _direccion = (unsigned int)Direcciones::Down;
        _sprPersonaje->setFrameY(_direccion);
        move(0, _velDesplaz);
    }
    if (_controller.isPressed(Controller::Buttons::ButtonShoot) && (_coolDown == 0)) {
        disparar();
    }

    if (_estado == (unsigned int)Estados::Caminando) {        
        animar();
        if (_pasos.getStatus() != _pasos.Playing) { // si no está sonando ya los pasos, se inicia el sonido
            _pasos.play(); // sonido de pasos
        }
    } else if(_estado == (unsigned int)Estados::Quieto) {
        _pasos.stop(); // para de sonar los pasos, porque está quieto
    }
    if (_coolDown > 0) {
        _coolDown--;
    }
}


void personaje::disparar()
{
    getJuegoActual().crearProyectil(getPosition());
    _coolDown = 30;
}

void personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_sprPersonaje->getSprite(), states);
}

sf::FloatRect personaje::getBounds()
{
    sf::FloatRect rect = sf::FloatRect(sf::Vector2f(getPosition().x, getPosition().y), sf::Vector2f(_sprPersonaje->getFrameSize().x, _sprPersonaje->getFrameSize().y));
    return rect;
}

