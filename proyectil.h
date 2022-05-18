#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "sprite.h"
#include "colisionable.h"
using namespace sf;

class proyectil: public colisionable
{
private:
    sprite*     _sprProyectil; /// Composición del objeto con propiedades y métodos propios para el manejo de sprites.
    Vector2f    _velocidad; /// Velocidad actual o posición donde se encuentra
    float       _velDesplaz; /// Velocidad a la cual camina
    //int         _direccion; /// Dirección a la que el jugador está mirando
public:
	proyectil(Vector2f posicion);
    sprite getSprite();
    void animar(); /// pose de la animación.
    void setVelocidad(Vector2f vel);
    void update();
    void respawn(Vector2f posicion);
    FloatRect getBounds() override;
};

