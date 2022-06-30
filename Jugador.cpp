#include "Jugador.h"

Jugador::Jugador(int sprClase, JuegoProyectil& juego, Controller& controller, int dificultad, int coolDownLastimado)
    : _juego(juego), _controller(controller), _caminando(false)
{
    if (sprClase == 1) {
        _sprite = new Sprite(sprClase, 4, 4, sf::Vector2f(0, 0), .1f);
        _velDesplaz = 3.5f;
        _direccion = Direcciones::Down;
        _coolDown = 30;
        _bufferPasos.loadFromFile("audio/paso.wav");
        _pasos.setBuffer(_bufferPasos);
        _pasos.setVolume(8.f);
        _pasos.setPitch(1.f);
        _bufferGolpe.loadFromFile("audio/golpe.wav");
        _golpe.setBuffer(_bufferGolpe);
        _golpe.setVolume(10.f);
        _golpe.setPitch(.9f);
        _coolDownLastimado = coolDownLastimado;
        switch (dificultad) ///  de acuerdo a la velocidad, asigno m�s o menos vida para el jugador.
        {
        case 1:
            _vida = 6;
            break;
        case 2:
            _vida = 4;
            break;
        case 3:
            _vida = 2;
            break;
        }
    }  
}


/// Gets
JuegoProyectil& Jugador::getJuegoActual()
{
    return _juego;
}

/// M�todos
void Jugador::update() {
    _velocidad = {};
    ///Chequeo las teclas
    _caminando = false; // inicio con el jugador asumi�ndolo como que no est� caminando.
    if (_controller.isPressed(Controller::Buttons::Left)) {
        _caminando = true; // jugador comienza a caminar
        _direccion = Direcciones::Left;
        _sprite->setFrameY((int)_direccion);
        _velocidad.x = -_velDesplaz;
    }
    else if (_controller.isPressed(Controller::Buttons::Right)) {
        _caminando = true; // jugador comienza a caminar
        _direccion = Direcciones::Right;
        _sprite->setFrameY((int)_direccion);
        _velocidad.x = _velDesplaz;
    }
    else if (_controller.isPressed(Controller::Buttons::Up)) {
        _caminando = true; // jugador comienza a caminar
        _direccion = Direcciones::Up;
        _sprite->setFrameY((int)_direccion);
        _velocidad.y = -_velDesplaz;
    }
    else if (_controller.isPressed(Controller::Buttons::Down)) {
        _caminando = true; // jugador comienza a caminar
        _direccion = Direcciones::Down;
        _sprite->setFrameY((int)_direccion);
        _velocidad.y = _velDesplaz;
    }

    move(_velocidad);

    if (_controller.isPressed(Controller::Buttons::ButtonShoot) && (_coolDown == 0)) {
        disparar();
    }

    if (_caminando) {
        _sprite->animar();
        if (_pasos.getStatus() != _pasos.Playing) { // si no est� sonando ya los pasos, se inicia el sonido
            _pasos.play(); // sonido de pasos
        }
    }
    else if (!_caminando) {
        _pasos.stop(); // para de sonar los pasos, porque est� quieto
        _sprite->setFrameX(0); // para que se ubique en el primer frame de cada fila de animaci�n.
    }
    if (_coolDown > 0) { /// coolDown para disparar
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

void Jugador::recibirGolpe(int vida)
{
    _vida -= vida;
    _lastimado = true;
    _golpe.play();
}

void Jugador::sumarVida(int vida)
{
    _vida += vida;
}


