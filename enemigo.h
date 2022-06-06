#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sprite.h"
#include "IColisionable.h"


class Enemigo : public sf::Drawable, public sf::Transformable, public IColisionable
{
    private:
        sf::Vector2f _velocidad; /// Velocidad actual o posici�n donde se encuentra
        float        _velDesplaz; /// Velocidad a la cual camina
        Sprite*      _sprite;
        int          _direccion; /// Direcci�n a la que el jugador est� mirando
    public:
        enum class Direcciones { Up, Left, Down, Right };
        /// Constructor
        Enemigo(sf::Vector2f posicion);
        /// Sets
        void          setSentidoX(int frame); /// Para conocer si est� mirando hacia la izquierda o derecha.
        void          setSentidoY(int frame); /// Para conocer si est� mirando hacia arriba o abajo
        void          setDireccion(int direccion);
        /// Gets
        const Sprite& getSprite(); ///obtengo el objeto sprite
        sf::Vector2f  getVelocidad();
        /// M�todos
        void          update();
        void          respawn(sf::Vector2f posicion);
        void          draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del m�todo draw en Drawable.
        const         sf::FloatRect getBounds() override;
};

