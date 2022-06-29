#pragma once
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include "IColisionable.h"

class Item: public sf::Drawable, public sf::Transformable, public IColisionable
{
	public:
		Item(int sprClase);
		void	 update();
		void	 draw(sf::RenderTarget& target, sf::RenderStates states) const override; 
		const    sf::FloatRect getBounds() override;
		void	 spawn(sf::Vector2f posicion);
		bool	 getVisible() const;
		void	 setVisible(bool visible);
	private:
		Sprite* _sprite;
		bool	_visible;
};

