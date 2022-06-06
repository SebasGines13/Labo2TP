#include "Bloque.h"

Bloque::Bloque(bool solid)
    :_solid(solid)
{
    _body.setSize(sf::Vector2f(16.f, 16.f));
}

void Bloque::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_body, states);
}

const sf::FloatRect Bloque::getBounds()/// dimensiones del bloque
{ 
    sf::FloatRect rect = _body.getGlobalBounds();
    rect.left = getPosition().x;
    rect.top = getPosition().y;
    return rect;
}

bool Bloque::isSolid() const
{
    return _solid;
}

void Bloque::setTextureBloque(sf::Texture& textura)
{
    _body.setTexture(&textura);
}

void Bloque::setTextureRectBloque(sf::IntRect rect)
{
    _body.setTextureRect(rect);
}
