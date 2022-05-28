#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sprite.h"
#include "IColisionable.h"

class Proyectil: public sf::Drawable, public sf::Transformable, public IColisionable
{
private:
    Sprite*         _sprProyectil; /// Composici�n del objeto con propiedades y m�todos propios para el manejo de sprites.
    sf::Vector2f    _velocidad; /// Velocidad actual o posici�n donde se encuentra
    float           _velDesplaz; /// Velocidad a la cual camina
    //int         _direccion; /// Direcci�n a la que el jugador est� mirando
public:
	Proyectil(sf::Vector2f posicion);
    Sprite getSprite();
    void animar(); /// pose de la animaci�n.
    void setVelocidad(sf::Vector2f vel);
    void update();
    void respawn(sf::Vector2f posicion);
    sf::FloatRect getBounds() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del m�todo draw en Drawable.
};

