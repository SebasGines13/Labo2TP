#include "bloque.h"

bloque::bloque(){
    _solido = false;
}

void bloque::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(_sprite, states);
}

bool bloque::esSolido(){
    return _solido;
}

void bloque::setSolido(bool solido){
    _solido = solido;
}

sf::FloatRect bloque::getBounds(){ /// dimensiones del bloque
    sf::FloatRect rect = sf::FloatRect(sf::Vector2f(getPosition().x, getPosition().y), sf::Vector2f(16.f, 16.f));
    return rect;
}


void bloque::setTextureBloque(sf::Texture& txtMapa) {
    _sprite.setTexture(txtMapa);
}

void bloque::setTextureRectBloque(sf::IntRect rect)
{
    _sprite.setTextureRect(rect);
}

void bloque::setColorBloque(sf::Color color)
{
    _sprite.setColor(color);
}
