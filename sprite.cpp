#include "sprite.h"
using namespace std;

///Constructor
sprite::sprite(int sprClase, int cantX, int cantY, Vector2f frameActual) {
    String path = "img/personaje" + to_string(sprClase) + ".png"; //contruyo la ruta para conocer la imagen actual del sprite.
    _sprActual = sprClase; //nro del sprite actual
    _txtPersonaje = new Texture();
    _txtPersonaje->loadFromFile(path);
    _sprPersonaje = new Sprite(*_txtPersonaje);
    _cantX = cantX;
    _cantY = cantY;
    _frameSize = Vector2f(_txtPersonaje->getSize().x / _cantX, _txtPersonaje->getSize().y / _cantY);
    _frameActual = frameActual;
    _sprPersonaje->setOrigin(_frameSize.x / 2, _frameSize.y / 2);
    _sprPersonaje->move(100.f, 100.f); /// Posición inicial del jugador en el mapa
    seleccionarFrame();
}

///sets
void sprite::setPosicion(Vector2f position) {
    _sprPersonaje->setPosition(position);
}

void sprite::setCantX(int cantX) {
    _cantX = cantX;
}

void sprite::setCantY(int cantY) {
    _cantY = cantY;
}

void sprite::setFrameSize(Vector2f frameSize) {
    _frameSize = frameSize;
}

void sprite::setFrameActual(Vector2f frameActual) {
    _frameActual = frameActual;
}

void sprite::setFrameX(int frame) {
    _frameActual.x = frame;
    seleccionarFrame();
}

void sprite::setFrameY(int frame) {
    _frameActual.y = frame;
    seleccionarFrame();
}


///gets
int sprite::getCantX() {
    return _cantX;
}

int sprite::getCantY() {
    return _cantY;
}

Vector2f sprite::getFrameSize() {
    return _frameSize;
}

Vector2f sprite::getFrameActual() {
    return _frameActual;
}

Sprite sprite::getSprite() {
    return *_sprPersonaje;
}


Vector2f sprite::getPosicion() {
    return _sprPersonaje->getPosition();
}


int sprite::getFrameX() {
    return _frameActual.x;
}

int sprite::getFrameY() {
    return _frameActual.y;
}


///Métodos
void sprite::seleccionarFrame() {
    IntRect rectangulo((int)(_frameActual.x) * _frameSize.x, _frameActual.y* _frameSize.y, _frameSize.x, _frameSize.y); /// Ubico el sprite que necesito recortar dentro de la textura.
    _sprPersonaje->setTextureRect(rectangulo); ///Recorto la textura.
}

void sprite::animarFrame() {
    if (_frameActual.x < _cantX-1 ) ///Si no es el último frame, avanzo a la siguiente posición del frame.
        _frameActual.x += .1f; ///Incremento el frame
    else _frameActual.x = 0; ///Si es el caso de que era el último, ahora se reinicia el ciclo de frames.
    seleccionarFrame(); ///Selecciono el rectángulo correspondiente al frame
}


