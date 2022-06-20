#pragma once
#include <SFML/Graphics.hpp>
#include "Sprite.h"

class Personaje
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
        // M�todos
        void             setSpriteQuieto(); /// Para conocer si est� mirando hacia la izquierda o derecha.
        virtual void     update() = 0;
        virtual void     spawn(sf::Vector2f posicion)=0;
    protected:
        sf::Vector2f     _velocidad; /// Velocidad actual o posici�n donde se encuentra
        float            _velDesplaz; /// Velocidad a la cual camina
        Direcciones      _direccion; /// Direcci�n a la que el jugador est� mirando
        int              _coolDown; /// tiempo de enfriamiento hasta que logre efectuan un nuevo disparo.
        Sprite*          _sprite;        
};

