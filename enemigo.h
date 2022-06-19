#pragma once
#include "Personaje.h"
#include "IColisionable.h"

class Enemigo : public Personaje, public sf::Drawable, public sf::Transformable, public IColisionable
{
    public:        
        /// Constructor
        Enemigo(int sprClase, sf::Vector2f posicion);
        /// Destructor
        ~Enemigo();
        /// Métodos
        void    draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
        void    update() override;
        void    spawn(sf::Vector2f posicion) override;
        const   sf::FloatRect getBounds() override;
};

