#pragma once
#include "Personaje.h"

class Enemigo : public Personaje
{
    public:        
        /// Constructor
        Enemigo(int sprClase, float velDesplaz, sf::Vector2f posicion);
        /// Destructor
        ~Enemigo();
        /// M�todos
        void    update() override;
        void    spawn(sf::Vector2f posicion) override;
        void    draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del m�todo draw en Drawable.
};

