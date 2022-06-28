#pragma once
#include <SFML/Audio.hpp>
#include "Controller.h"
#include "Personaje.h"
#include "JuegoProyectil.h"

class Jugador : public Personaje
{
	public:
        /// Constructor
        Jugador(int sprClase, JuegoProyectil& juego, Controller& controller, int dificultad);
        /// Sets
        void            setLastimado(const bool &lastimado);
        /// Gets
        JuegoProyectil& getJuegoActual(); /// retorna referencia la juego actual.
        /// M�todos
        void            disparar(); // m�todo para disparar proyectil
        void            draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del m�todo draw en Drawable.
        void            update() override;
        void            recibirGolpe(int vida) override;
    private:
        JuegoProyectil& _juego; /// instancia del juego utilizada para crear disparar proyectil
        Controller&     _controller; /// referencia de controller para saber cu�l es el que le corresponde
        sf::SoundBuffer _buffer;  /// buffer para el sonido
        sf::Sound       _pasos;   /// canal utilizado por el buffer
        bool            _caminando;
        bool            _lastimado;
};

