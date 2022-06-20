#pragma once
#include "Personaje.h"

class Enemigo : public Personaje
{
    public:        
        /// Constructor
        Enemigo(int sprClase, sf::Vector2f posicion);
        /// Destructor
        ~Enemigo();
        /// M�todos
        void    update() override;
        void    spawn(sf::Vector2f posicion) override;
};

