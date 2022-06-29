#include "Item.h"

Item::Item(int sprClase)
{
	if (sprClase == 1) {
		_sprite = new Sprite(30, 33, 1, sf::Vector2f(0, 0), .35f);
	}else if (sprClase == 2) {
		_sprite = new Sprite(32, 10, 1, sf::Vector2f(0, 0), .25f);
	}
	_visible = false;
}


void Item::update()
{
	_sprite->animar();
}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_sprite->getSprite(), states);
}

const sf::FloatRect Item::getBounds()
{
	sf::FloatRect rect = sf::FloatRect(sf::Vector2f(getPosition().x, getPosition().y), sf::Vector2f(_sprite->getFrameSize().x, _sprite->getFrameSize().y));
	return rect;
}

void Item::spawn(sf::Vector2f posicion)
{
	setPosition(posicion);
}

bool Item::getVisible() const
{
	return _visible;
}

void Item::setVisible(bool visible)
{
	_visible = visible;
}
