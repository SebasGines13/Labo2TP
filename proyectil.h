#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sprite.h"
#include "IColisionable.h"

class Proyectil: public sf::Drawable, public sf::Transformable, public IColisionable
{
private:
    Sprite*         _sprProyectil; /// Composición del objeto con propiedades y métodos propios para el manejo de sprites.
    sf::Vector2f    _velocidad; /// Velocidad actual o posición donde se encuentra
    float           _velDesplaz; /// Velocidad a la cual camina
    //int         _direccion; /// Dirección a la que el jugador está mirando
public:
	Proyectil(sf::Vector2f posicion);
    Sprite getSprite();
    void animar(); /// pose de la animación.
    void setVelocidad(sf::Vector2f vel);
    void update();
    void respawn(sf::Vector2f posicion);
    sf::FloatRect getBounds() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
};

