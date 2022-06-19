#include "Jugador.h"

Jugador::Jugador(int sprClase, JuegoProyectil& juego, Controller& controller)
    : _juego(juego), _controller(controller), _lastimado(false), _estado(Estados::Quieto)
{
    if (sprClase == 1) {
        _sprite = new Sprite(sprClase, 4, 4, sf::Vector2f(0, 0), .1f);
        _velDesplaz = 3.5f;
        _velocidad = sf::Vector2f(0, 0);
        _direccion = Direcciones::Down;
        _coolDown = 30;
        _buffer.loadFromFile("audio/paso.wav");
        _pasos.setBuffer(_buffer);
        _pasos.setVolume(10.f);
        _pasos.setPitch(1.f);
    }  
}

void Jugador::setLastimado(const bool& lastimado)
{
    _lastimado = lastimado;
}

/// Gets
JuegoProyectil& Jugador::getJuegoActual()
{
    return _juego;
}

/// Métodos
void Jugador::update() {
    _velocidad = {};
    ///Chequeo las teclas
    _estado = Estados::Quieto; // inicio con el jugador asumiéndolo como que no está caminando.
    if (_controller.isPressed(Controller::Buttons::Left)) {
        _estado = Estados::Caminando; // jugador comienza a caminar
        _direccion = Direcciones::Left;
        _sprite->setFrameY((int)_direccion);
        _velocidad.x = -_velDesplaz;
    }
    else if (_controller.isPressed(Controller::Buttons::Right)) {
        _estado = Estados::Caminando; // jugador comienza a caminar
        _direccion = Direcciones::Right;
        _sprite->setFrameY((int)_direccion);
        _velocidad.x = _velDesplaz;
    }
    else if (_controller.isPressed(Controller::Buttons::Up)) {
        _estado = Estados::Caminando; // jugador comienza a caminar
        _direccion = Direcciones::Up;
        _sprite->setFrameY((int)_direccion);
        _velocidad.y = -_velDesplaz;
    }
    else if (_controller.isPressed(Controller::Buttons::Down)) {
        _estado = Estados::Caminando; // jugador comienza a caminar
        _direccion = Direcciones::Down;
        _sprite->setFrameY((int)_direccion);
        _velocidad.y = _velDesplaz;
    }

    move(_velocidad);

    if (_controller.isPressed(Controller::Buttons::ButtonShoot) && (_coolDown == 0)) {
        disparar();
    }

    if (_estado == Estados::Caminando) {
        _sprite->animar();
        if (_pasos.getStatus() != _pasos.Playing) { // si no está sonando ya los pasos, se inicia el sonido
            _pasos.play(); // sonido de pasos
        }
    }
    else if (_estado == Estados::Quieto) {
        _pasos.stop(); // para de sonar los pasos, porque está quieto
        _sprite->setFrameX(0); // para que se ubique en el primer frame de cada fila de animación.
    }
    if (_coolDown > 0) {
        _coolDown--;
    }
}



void Jugador::disparar()
{
    getJuegoActual().crearProyectil(getPosition());
    _coolDown = 30;
}

void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (_lastimado) _sprite->setColor(sf::Color(255, 0, 0, 255));
    else _sprite->setColor(sf::Color(255, 255, 255, 255));
    states.transform *= getTransform();
    target.draw(_sprite->getSprite(), states);
}

void Jugador::spawn(sf::Vector2f posicion) {
    setPosition(posicion);
}

const sf::FloatRect Jugador::getBounds()
{
    sf::FloatRect rect = sf::FloatRect(sf::Vector2f(getPosition().x, getPosition().y), sf::Vector2f(_sprite->getFrameSize().x, _sprite->getFrameSize().y));
    return rect;
}

