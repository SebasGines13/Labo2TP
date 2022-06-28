#pragma once
#include <SFML/Graphics.hpp>
#include "Proyectil.h"

class JuegoProyectil
{
public:
	virtual void crearProyectil(sf::Vector2f posicion, Proyectil::Direcciones direccion) = 0; /// Es un método sobreescribible y quien lo herede está obligado a definir como se crea el proyectil.
};

