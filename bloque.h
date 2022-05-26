#pragma once
#include <SFML/Graphics.hpp>
#include "colisionable.h"

class bloque: public sf::Drawable, public sf::Transformable, public colisionable
{
protected:
	sf::RectangleShape	_body;
	bool				_solid;
	sf::Texture			_texture;
public:
	bloque();
	void				draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
	sf::FloatRect		getBounds();
	bool				isSolid() const;
	void				setTextureBloque(sf::Texture &textura);
	void				setTextureRectBloque(sf::IntRect rect);
};

