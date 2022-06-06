#pragma once
#include <SFML/Graphics.hpp>
#include "IColisionable.h"

class Bloque: public sf::Drawable, public sf::Transformable, public IColisionable
{
	private:
		sf::RectangleShape	_body;
		bool				_solid;
		sf::Texture			_texture;
	public:
		/// Constructor
		Bloque(bool solid);
		/// sets
		void				 setTextureBloque(sf::Texture& textura);
		void				 setTextureRectBloque(sf::IntRect rect);
		/// gets
		const sf::FloatRect  getBounds();
		bool				 isSolid() const;
		/// Métodos
		void				 draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
};

