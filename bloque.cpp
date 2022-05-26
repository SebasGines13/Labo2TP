#include "bloque.h"

bloque::bloque()
    :_solid(false)
{
    _body.setSize(sf::Vector2f(16.f, 16.f));
    /*_texture.loadFromFile("img/dungeon.png");
    _body.setTexture(&_texture);
    */
}

void bloque::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_body, states);
}

sf::FloatRect bloque::getBounds()/// dimensiones del bloque
{ 
    sf::FloatRect rect = _body.getGlobalBounds();
    rect.left = getPosition().x;
    rect.top = getPosition().y;
    return rect;
}

bool bloque::isSolid() const
{
    return _solid;
}

void bloque::setTextureBloque(sf::Texture& textura)
{
    _body.setTexture(&textura);
}

void bloque::setTextureRectBloque(sf::IntRect rect)
{
    _body.setTextureRect(rect);
}
