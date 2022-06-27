#include "Sprite.h"

///Constructor
Sprite::Sprite(int sprClase, int cantX, int cantY, sf::Vector2f frameActual, float velAnima) {
    std::string path = "img/" + std::to_string(sprClase) + ".png"; //contruyo la ruta para conocer la imagen actual del sprite.
    _textura = new sf::Texture();
    _textura->loadFromFile(path);
    _sprite = new sf::Sprite(*_textura);
    _cantX = cantX;
    _cantY = cantY;
    _frameSize = sf::Vector2f((float)_textura->getSize().x / _cantX, (float)_textura->getSize().y / _cantY);
    _frameActual = frameActual;
    _velAnima = velAnima;
    seleccionarFrame();
}

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
    delete _textura;
    delete _sprite;
}

///sets
void Sprite::setPosicion(sf::Vector2f position) {
    _sprite->setPosition(position);
}

void Sprite::setFrameX(float frame) {
    _frameActual.x = frame;
    seleccionarFrame();
}

void Sprite::setFrameY(float frame) {
    _frameActual.y = frame;
    seleccionarFrame();
}

///gets
sf::Vector2f Sprite::getFrameSize() {
    return _frameSize;
}

sf::Sprite Sprite::getSprite() {
    return *_sprite;
}

///M�todos
void Sprite::seleccionarFrame() {
    sf::IntRect rectangulo((int)(_frameActual.x) * (int)_frameSize.x, (int)_frameActual.y* (int)_frameSize.y, (int)_frameSize.x, (int)_frameSize.y); /// Ubico el sprite que necesito recortar dentro de la textura.
    _sprite->setTextureRect(rectangulo); ///Recorto la textura.
}

void Sprite::animar() {
    if (_frameActual.x < _cantX-1 ) ///Si no es el �ltimo frame, avanzo a la siguiente posici�n del frame.
        _frameActual.x += _velAnima; ///Incremento el frame
    else _frameActual.x = 0; ///Si es el caso de que era el �ltimo, ahora se reinicia el ciclo de frames.
    seleccionarFrame(); ///Selecciono el rect�ngulo correspondiente al frame
}

void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(*_sprite, states);
}

void Sprite::setColor(sf::Color color) {
    _sprite->setColor(color);
}