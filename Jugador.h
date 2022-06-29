#pragma once
#include <SFML/Audio.hpp>
#include "Controller.h"
#include "Personaje.h"
#include "JuegoProyectil.h"

class Jugador : public Personaje
{
	public:
        /// Constructor
        Jugador(int sprClase, JuegoProyectil& juego, Controller& controller, int dificultad, int coolDownLastimado);
        /// Gets
        JuegoProyectil& getJuegoActual(); /// retorna referencia la juego actual.
        /// Métodos
        void            disparar(); // método para disparar proyectil
        void            draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
        void            update() override;
        void            recibirGolpe(int vida) override;
        void            sumarVida(int vida);
    private:
        JuegoProyectil& _juego; /// instancia del juego utilizada para crear disparar proyectil
        Controller&     _controller; /// referencia de controller para saber cuál es el que le corresponde
        sf::SoundBuffer _buffer;  /// buffer para el sonido
        sf::Sound       _pasos;   /// canal utilizado por el buffer
        bool            _caminando;
};

