#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "sprite.h"
#include "colisionable.h"
using namespace sf;

class proyectil: public colisionable
{
private:
    sprite*     _sprProyectil; /// Composici�n del objeto con propiedades y m�todos propios para el manejo de sprites.
    Vector2f    _velocidad; /// Velocidad actual o posici�n donde se encuentra
    float       _velDesplaz; /// Velocidad a la cual camina
    //int         _direccion; /// Direcci�n a la que el jugador est� mirando
public:
	proyectil(Vector2f posicion);
    sprite getSprite();
    void animar(); /// pose de la animaci�n.
    void setVelocidad(Vector2f vel);
    void update();
    void respawn(Vector2f posicion);
    FloatRect getBounds() override;
};

