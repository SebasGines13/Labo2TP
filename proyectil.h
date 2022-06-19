#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sprite.h"
#include "IColisionable.h"

class Proyectil: public sf::Drawable, public sf::Transformable, public IColisionable
{
    private:
        sf::Vector2f    _velocidad; /// Velocidad actual o posición donde se encuentra
        float           _velDesplaz; /// Velocidad a la cual camina
        Sprite*         _sprite;
    public:
        enum class Direcciones { Down, Left, Right, Up };
        /// Constructor
	    Proyectil(sf::Vector2f posicion);
        /// Destructor
        ~Proyectil();
        /// Gets
        Sprite getSprite();
        /// Sets
        void setVelocidad(sf::Vector2f vel);
        /// Métodos
        void update();
        void respawn(sf::Vector2f posicion);
        const sf::FloatRect getBounds() override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
};

