#pragma once
#include "Personaje.h"

class Enemigo : public Personaje
{
    public:        
        /// Constructor
        Enemigo(int sprClase, sf::Vector2f posicion);
        /// Destructor
        ~Enemigo();
        /// Gets
        int     getTipoEnemigo();
        /// M�todos
        void    update() override;
        void    recibirGolpe(int vida) override;
    private:
        int     _tipoEnemigo;
        void    colorSegunVida();
};

