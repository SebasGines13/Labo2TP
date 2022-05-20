#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "sprite.h"
#include "colisionable.h"

class proyectil: public sf::Drawable, public sf::Transformable, public colisionable
{
private:
    sprite*         _sprProyectil; /// Composición del objeto con propiedades y métodos propios para el manejo de sprites.
    sf::Vector2f    _velocidad; /// Velocidad actual o posición donde se encuentra
    float           _velDesplaz; /// Velocidad a la cual camina
    //int         _direccion; /// Dirección a la que el jugador está mirando
public:
	proyectil(sf::Vector2f posicion);
    sprite getSprite();
    void animar(); /// pose de la animación.
    void setVelocidad(sf::Vector2f vel);
    void update();
    void respawn(sf::Vector2f posicion);
    sf::FloatRect getBounds() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
};

