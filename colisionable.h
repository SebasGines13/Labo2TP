#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;


// Clases abstractas -- Interfaces
class colisionable
{
	public:
		bool isCollision(colisionable& obj); /// Evaluamos colisiones con otro objeto colisionable, mediante la intersección de cajas
		virtual FloatRect getBounds() = 0; /// al ser virtual, este método se puede escribir, pero al poner en 0 ese método no tiene implementación, sino que debe desarrollarse en cada clase derivada.

};

