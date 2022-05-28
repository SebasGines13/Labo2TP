#include "Personaje.h"

///Constructor
Personaje::Personaje(int sprClase, int cantX, int cantY, sf::Vector2f frameActual, JuegoProyectil& juego, Controller& controller)
    : _juego(juego), _controller(controller)
{
    _sprPersonaje = new Sprite(sprClase, cantX, cantY, frameActual, .1f);
    _velDesplaz = 3.5f;
    _velocidad = sf::Vector2f(0, 0);
    _estado = (unsigned int)Estados::Quieto;
    _direccion = (unsigned int)Direcciones::Down;
    _buffer.loadFromFile("audio/paso.wav");
    _pasos.setBuffer(_buffer);
    _pasos.setVolume(10.f);
    _pasos.setPitch(1.f);
    _coolDown = 30;
}

///sets
void Personaje::setVelDesplaz(float velDesplaz) {
    _velDesplaz = velDesplaz;
}

///gets
const Sprite& Personaje::getSpritePersonaje(){
    return *_sprPersonaje;
}

const float& Personaje::getVelDesplaz(){
    return _velDesplaz;
}

const unsigned int& Personaje::getDireccion(){
    return _direccion;
}

JuegoProyectil& Personaje::getJuegoActual(){
    return _juego;
}

const sf::Vector2f& Personaje::getVelocidad() {
    return _velocidad;
}


///Métodos
void Personaje::setSentidoX(float frame) {
    _sprPersonaje->setFrameX(frame);
}

void Personaje::setSentidoY(float frame) {
    _sprPersonaje->setFrameY(frame);
}

void Personaje::animar() {
    _sprPersonaje->animarFrame();
}

void Personaje::update() {
    _velocidad = {};
    ///Chequeo las teclas
    _estado = (unsigned int)Estados::Quieto; // inicio con el jugador asumiéndolo como que no está caminando.
    if (_controller.isPressed(Controller::Buttons::Left)) {
        _estado = (unsigned int)Estados::Caminando; // jugador comienza a caminar
        _direccion = (unsigned int)Direcciones::Left;
        _sprPersonaje->setFrameY(_direccion);
        _velocidad.x = -_velDesplaz;
    }
    else if (_controller.isPressed(Controller::Buttons::Right)) {
        _estado = (unsigned int)Estados::Caminando; // jugador comienza a caminar
        _direccion = (unsigned int)Direcciones::Right;
        _sprPersonaje->setFrameY(_direccion);
        _velocidad.x = _velDesplaz;
    }
    else if (_controller.isPressed(Controller::Buttons::Up)) {
        _estado = (unsigned int)Estados::Caminando; // jugador comienza a caminar
        _direccion = (unsigned int)Direcciones::Up;
        _sprPersonaje->setFrameY(_direccion);
        _velocidad.y = -_velDesplaz;
    }
    else if (_controller.isPressed(Controller::Buttons::Down)) {
        _estado = (unsigned int)Estados::Caminando; // jugador comienza a caminar
        _direccion = (unsigned int)Direcciones::Down;
        _sprPersonaje->setFrameY(_direccion);
        _velocidad.y = _velDesplaz;
    }

    move(_velocidad);

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


void Personaje::disparar()
{
    getJuegoActual().crearProyectil(getPosition());
    _coolDown = 30;
}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_sprPersonaje->getSprite(), states);
}

sf::FloatRect Personaje::getBounds()
{
    sf::FloatRect rect = sf::FloatRect(sf::Vector2f(getPosition().x, getPosition().y), sf::Vector2f(_sprPersonaje->getFrameSize().x, _sprPersonaje->getFrameSize().y));
    return rect;
}

