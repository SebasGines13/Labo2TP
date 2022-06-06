#include "Personaje.h"

///Constructor
Personaje::Personaje(int sprClase, int cantX, int cantY, sf::Vector2f frameActual, JuegoProyectil& juego, Controller& controller)
    : _juego(juego), _controller(controller)
{
    _sprite = new Sprite(sprClase, cantX, cantY, frameActual, .1f);
    _velDesplaz = 3.5f;
    _velocidad = sf::Vector2f(0, 0);
    _estado = (int)Estados::Quieto;
    _direccion = (int)Direcciones::Down;
    _buffer.loadFromFile("audio/paso.wav");
    _pasos.setBuffer(_buffer);
    _pasos.setVolume(10.f);
    _pasos.setPitch(1.f);
    _coolDown = 30;
    _lastimado = false;
}

///sets
void Personaje::setLastimado(bool b)
{
    _lastimado = b;
}

sf::Vector2f Personaje::getVelocidad()
{
    return _velocidad;
}

///gets
JuegoProyectil& Personaje::getJuegoActual() 
{
    return _juego;
}


///Métodos
void Personaje::setSentidoX(float frame) {
    _sprite->setFrameX(frame);
}

void Personaje::setSentidoY(float frame) {
    _sprite->setFrameY(frame);
}

void Personaje::update() {
    _velocidad = {};
    ///Chequeo las teclas
    _estado = (int)Estados::Quieto; // inicio con el jugador asumiéndolo como que no está caminando.
    if (_controller.isPressed(Controller::Buttons::Left)) {
        _estado = (int)Estados::Caminando; // jugador comienza a caminar
        _direccion = (int)Direcciones::Left;
        _sprite->setFrameY(_direccion);
        _velocidad.x = -_velDesplaz;
    }
    else if (_controller.isPressed(Controller::Buttons::Right)) {
        _estado = (int)Estados::Caminando; // jugador comienza a caminar
        _direccion = (int)Direcciones::Right;
        _sprite->setFrameY(_direccion);
        _velocidad.x = _velDesplaz;
    }
    else if (_controller.isPressed(Controller::Buttons::Up)) {
        _estado = (int)Estados::Caminando; // jugador comienza a caminar
        _direccion = (int)Direcciones::Up;
        _sprite->setFrameY(_direccion);
        _velocidad.y = -_velDesplaz;
    }
    else if (_controller.isPressed(Controller::Buttons::Down)) {
        _estado = (int)Estados::Caminando; // jugador comienza a caminar
        _direccion = (int)Direcciones::Down;
        _sprite->setFrameY(_direccion);
        _velocidad.y = _velDesplaz;
    }

    move(_velocidad);

    if (_controller.isPressed(Controller::Buttons::ButtonShoot) && (_coolDown == 0)) {
        disparar();
    }

    if (_estado == (int)Estados::Caminando) {
        _sprite->animar();
        if (_pasos.getStatus() != _pasos.Playing) { // si no está sonando ya los pasos, se inicia el sonido
            _pasos.play(); // sonido de pasos
        }
    } else if(_estado == (int)Estados::Quieto) {
        _pasos.stop(); // para de sonar los pasos, porque está quieto
        _sprite->setFrameX(0); // para que se ubique en el primer frame de cada fila de animación.
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
    if (_lastimado) _sprite->setColor(sf::Color(255, 0, 0, 255));
    else _sprite->setColor(sf::Color(255, 255, 255, 255));
    states.transform *= getTransform();
    target.draw(_sprite->getSprite(), states);
}

const sf::FloatRect Personaje::getBounds()
{
    sf::FloatRect rect = sf::FloatRect(sf::Vector2f(getPosition().x, getPosition().y), sf::Vector2f(_sprite->getFrameSize().x, _sprite->getFrameSize().y));
    return rect;
}

