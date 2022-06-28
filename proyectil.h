#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sprite.h"
#include "IColisionable.h"

class Proyectil: public sf::Drawable, public sf::Transformable, public IColisionable
{
    public:
        /// Constructor
	    Proyectil(sf::Vector2f posicion);
        /// Destructor
        ~Proyectil();
        /// Gets
        Sprite getSprite();
        /// Sets
        void setVelocidad(sf::Vector2f vel);
        /// M�todos
        void update();
        void respawn(sf::Vector2f posicion);
        void playSonido();
        const sf::FloatRect getBounds() override;
        void  draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del m�todo draw en Drawable.
    private:
        sf::Vector2f    _velocidad; /// Velocidad actual o posici�n donde se encuentra
        float           _velDesplaz; /// Velocidad a la cual camina
        Sprite*         _sprite;
        sf::SoundBuffer _buffer;  /// buffer para el sonido
        sf::Sound       _sonido;   /// canal utilizado por el buffer
};

