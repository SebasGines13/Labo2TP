#pragma once
#include "Personaje.h"

class Enemigo : public Personaje
{
    public:        
        /// Constructor
        Enemigo(int tipoEnemigo, sf::Vector2f posicion, int dificultad, const int& coolDownLastimado);
        /// Destructor
        ~Enemigo();
        /// Gets
        int     getTipoEnemigo();
        /// Métodos
        void    update() override;
        void    recibirGolpe(int vida) override;
    private:
        int     _tipoEnemigo;
        int     _coolDownInicialDireccion;
        void    colorSegunVida();
};

