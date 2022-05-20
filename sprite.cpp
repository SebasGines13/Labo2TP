#include "sprite.h"

///Constructor
sprite::sprite(int sprClase, int cantX, int cantY, sf::Vector2f frameActual, float velAnima) {
    std::string path = "img/" + std::to_string(sprClase) + ".png"; //contruyo la ruta para conocer la imagen actual del sprite.
    _sprActual = sprClase; //nro del sprite actual
    _txtPersonaje = new sf::Texture();
    _txtPersonaje->loadFromFile(path);
    _sprPersonaje = new sf::Sprite(*_txtPersonaje);
    _cantX = cantX;
    _cantY = cantY;
    _frameSize = sf::Vector2f(_txtPersonaje->getSize().x / _cantX, _txtPersonaje->getSize().y / _cantY);
    _frameActual = frameActual;
    _velAnima = velAnima;
    seleccionarFrame();
}

///sets
void sprite::setPosicion(sf::Vector2f position) {
    _sprPersonaje->setPosition(position);
}

void sprite::setCantX(int cantX) {
    _cantX = cantX;
}

void sprite::setCantY(int cantY) {
    _cantY = cantY;
}

void sprite::setFrameSize(sf::Vector2f frameSize) {
    _frameSize = frameSize;
}

void sprite::setFrameActual(sf::Vector2f frameActual) {
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

sf::Vector2f sprite::getFrameSize() {
    return _frameSize;
}

sf::Vector2f sprite::getFrameActual() {
    return _frameActual;
}

sf::Sprite sprite::getSprite() {
    return *_sprPersonaje;
}


sf::Vector2f sprite::getPosicion() {
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
    sf::IntRect rectangulo((int)(_frameActual.x) * _frameSize.x, _frameActual.y* _frameSize.y, _frameSize.x, _frameSize.y); /// Ubico el sprite que necesito recortar dentro de la textura.
    _sprPersonaje->setTextureRect(rectangulo); ///Recorto la textura.
}

void sprite::animarFrame() {
    if (_frameActual.x < _cantX-1 ) ///Si no es el último frame, avanzo a la siguiente posición del frame.
        _frameActual.x += _velAnima; ///Incremento el frame
    else _frameActual.x = 0; ///Si es el caso de que era el último, ahora se reinicia el ciclo de frames.
    seleccionarFrame(); ///Selecciono el rectángulo correspondiente al frame
}


