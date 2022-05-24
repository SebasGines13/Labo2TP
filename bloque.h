#pragma once
#include <SFML/Graphics.hpp>
#include "colisionable.h"

class bloque: public sf::Drawable, public sf::Transformable, public colisionable
{
private:
	sf::Sprite			_sprite;
	bool				_solido;
public:
	bloque();
	void				draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
	bool				esSolido();
	void				setSolido(bool solido);
	sf::FloatRect		getBounds();
	void				setTextureBloque(sf::Texture& txtMapa);
	void				setTextureRectBloque(sf::IntRect rect);
	void				setColorBloque(sf::Color color);
};

