#pragma once
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include "IColisionable.h"

class Personaje: public sf::Drawable, public sf::Transformable, public IColisionable
{
    public:
        enum class Direcciones { Down, Left, Right, Up };
        // Constructor
        Personaje();
        // sets
        void             setDireccion(Direcciones direccion);
        // gets
        Direcciones      getDireccion();
        sf::Vector2f     getVelocidad();
        const Sprite&    getSprite(); ///obtengo el objeto sprite     
        // Métodos
        const sf::FloatRect getBounds() override;
        void                draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
        void                setSpriteQuieto(); /// Para conocer si está mirando hacia la izquierda o derecha.
        virtual void        update() = 0;
        virtual void        spawn(sf::Vector2f posicion)=0;
    protected:
        sf::Vector2f     _velocidad; /// Velocidad actual o posición donde se encuentra
        float            _velDesplaz; /// Velocidad a la cual camina
        Direcciones      _direccion; /// Dirección a la que el jugador está mirando
        int              _coolDown; /// tiempo de enfriamiento hasta que logre efectuan un nuevo disparo.
        Sprite*          _sprite;        
};

