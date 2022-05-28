#pragma once
#include <SFML/Graphics.hpp>

class JuegoProyectil
{
public:
	virtual void crearProyectil(sf::Vector2f posicion) = 0; /// Es un método sobreescribible y quien lo herede está obligado a definir como se crea el proyectil.
};

