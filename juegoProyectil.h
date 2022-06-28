#pragma once
#include <SFML/Graphics.hpp>
#include "Proyectil.h"

class JuegoProyectil
{
public:
	virtual void crearProyectil(sf::Vector2f posicion) = 0; /// Es un m�todo sobreescribible y quien lo herede est� obligado a definir como se crea el proyectil.
};

