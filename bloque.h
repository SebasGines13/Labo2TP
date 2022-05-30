#pragma once
#include <SFML/Graphics.hpp>
#include "IColisionable.h"

class Bloque: public sf::Drawable, public sf::Transformable, public IColisionable
{
protected:
	sf::RectangleShape	_body;
	bool				_solid;
	sf::Texture			_texture;
public:
	Bloque();
	void				 draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
	const sf::FloatRect  getBounds();
	bool				 isSolid() const;
	void				 setTextureBloque(sf::Texture &textura);
	void				 setTextureRectBloque(sf::IntRect rect);
};

