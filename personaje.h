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
        int                 _estado; /// enum para chequear estados, como por ejemplo si el jugador est� caminando o no.
        sf::Vector2f        _velocidad; /// Velocidad actual o posici�n donde se encuentra
        float               _velDesplaz; /// Velocidad a la cual camina
        int                 _direccion; /// Direcci�n a la que el jugador est� mirando
        sf::SoundBuffer     _buffer;  /// buffer para el sonido
        sf::Sound           _pasos;   /// canal utilizado por el buffer
        JuegoProyectil&     _juego; /// instancia del juego utilizada para crear disparar proyectil
        int                 _coolDown; /// tiempo de enfriamiento hasta que logre efectuan un nuevo disparo.
        Controller&         _controller; /// referencia de controller para saber cu�l es el que le corresponde
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
        //M�todos
        void            setSentidoX(float frame); /// Para conocer si est� mirando hacia la izquierda o derecha.
        void            setSentidoY(float frame); /// Para conocer si est� mirando hacia arriba o abajo
        void            update(); /// Actualiza las f�sicas del jugador.
        void            disparar(); // m�todo para disparar proyectil
        void            draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del m�todo draw en Drawable.
        const sf::FloatRect   getBounds() override;
};

