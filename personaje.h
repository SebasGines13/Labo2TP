#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sprite.h"
#include "juegoProyectil.h"
#include "IColisionable.h"
#include "Controller.h"


class Personaje: public sf::Drawable, public sf::Transformable, public IColisionable
{
    private:
        int                 _estado; /// enum para chequear estados, como por ejemplo si el jugador está caminando o no.
        sf::Vector2f        _velocidad; /// Velocidad actual o posición donde se encuentra
        float               _velDesplaz; /// Velocidad a la cual camina
        int                 _direccion; /// Dirección a la que el jugador está mirando
        sf::SoundBuffer     _buffer;  /// buffer para el sonido
        sf::Sound           _pasos;   /// canal utilizado por el buffer
        JuegoProyectil&     _juego; /// instancia del juego utilizada para crear disparar proyectil
        int                 _coolDown; /// tiempo de enfriamiento hasta que logre efectuan un nuevo disparo.
        Controller&         _controller; /// referencia de controller para saber cuál es el que le corresponde
        Sprite*             _sprite;
        bool                _lastimado;
    public:
        enum class Estados     {Quieto, Caminando};
        enum class Direcciones {Down, Left, Right, Up};
        //constructor
        Personaje(int sprClase, int cantX, int cantY, sf::Vector2f frameActual, JuegoProyectil& juego, Controller& controller);
        //sets
        void              setLastimado(bool b);
        //gets
        sf::Vector2f     getVelocidad();
        JuegoProyectil&  getJuegoActual(); /// retorna referencia la juego actual.
        //Métodos
        void            setSentidoX(float frame); /// Para conocer si está mirando hacia la izquierda o derecha.
        void            setSentidoY(float frame); /// Para conocer si está mirando hacia arriba o abajo
        void            update(); /// Actualiza las físicas del jugador.
        void            disparar(); // método para disparar proyectil
        void            draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
        const sf::FloatRect   getBounds() override;
};

