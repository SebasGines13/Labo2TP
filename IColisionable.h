#pragma once
#include <SFML/Graphics.hpp>


// Clases abstractas -- Interfaces
class IColisionable
{
	public:
		bool isCollision(IColisionable& obj); /// Evaluamos colisiones con otro objeto colisionable, mediante la intersecci�n de cajas
		virtual const sf::FloatRect getBounds() = 0; /// al ser virtual, este m�todo se puede escribir, pero al poner en 0 ese m�todo no tiene implementaci�n, sino que debe desarrollarse en cada clase derivada.
};

