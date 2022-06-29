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
        void                setDireccion(Direcciones direccion);
        void                setLastimado(bool lastimado);
        void                setCoolDownLastimado(int coolDown);
        // gets
        Direcciones         getDireccion();
        sf::Vector2f        getVelocidad();
        const float         getVelDesplaz();
        const Sprite&       getSprite(); ///obtengo el objeto sprite
        int                 getVida();
        bool                getLastimado();
        int                 getCoolDownLastimado();
        // Métodos
        const sf::FloatRect getBounds() override;
        void                draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
        void                setSpriteQuieto(); /// Para conocer si está mirando hacia la izquierda o derecha.
        void                spawn(sf::Vector2f posicion);
        virtual void        update() = 0;
        virtual void        recibirGolpe(int vida) = 0;
    protected:
        sf::Vector2f        _velocidad; /// Velocidad actual o posición donde se encuentra
        float               _velDesplaz; /// Velocidad a la cual camina
        Direcciones         _direccion; /// Dirección a la que el jugador está mirando
        int                 _coolDown; /// tiempo de enfriamiento hasta que logre efectuan un nuevo disparo en el caso de la clase Jugador o de cambio de direccion en el caso de enemigos.
        Sprite*             _sprite;
        int                 _vida;
        bool                _lastimado;
        int                 _coolDownLastimado;
};

