#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class juegoProyectil
{
public:
	virtual void crearProyectil(Vector2f posicion) = 0; /// Es un m�todo sobreescribible y quien lo herede est� obligado a definir como se crea el proyectil.
};

