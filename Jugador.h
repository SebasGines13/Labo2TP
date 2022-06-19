#pragma once
#include <SFML/Audio.hpp>
#include "Controller.h"
#include "Personaje.h"
#include "JuegoProyectil.h"
#include "IColisionable.h"

class Jugador: public Personaje, public sf::Drawable, public sf::Transformable, public IColisionable
{
	public:
        enum class Estados { Quieto, Caminando };
        /// Constructor
        Jugador(int sprClase, JuegoProyectil& juego, Controller& controller);
        /// Sets
        void            setLastimado(const bool &lastimado);
        /// Gets
        JuegoProyectil& getJuegoActual(); /// retorna referencia la juego actual.
        /// Métodos
        void            disparar(); // método para disparar proyectil
        void            draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
        void            update() override;
        void            spawn(sf::Vector2f posicion) override;
        const           sf::FloatRect getBounds() override;
    private:
        Estados         _estado; /// enum para chequear estados, como por ejemplo si el jugador está caminando o no.
        JuegoProyectil& _juego; /// instancia del juego utilizada para crear disparar proyectil
        Controller&     _controller; /// referencia de controller para saber cuál es el que le corresponde
        bool            _lastimado;
        sf::SoundBuffer _buffer;  /// buffer para el sonido
        sf::Sound       _pasos;   /// canal utilizado por el buffer

};

