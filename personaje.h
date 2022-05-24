#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "sprite.h"
#include "juegoProyectil.h"
#include "colisionable.h"
#include "Controller.h"


class personaje: public sf::Drawable, public sf::Transformable, public colisionable
{
    private:
        sprite              *_sprPersonaje; /// Composición del objeto con propiedades y métodos propios para el manejo de sprites.
        unsigned int        _estado; /// enum para chequear estados, como por ejemplo si el jugador está caminando o no.
        sf::Vector2f        _velocidad; /// Velocidad actual o posición donde se encuentra
        float               _velDesplaz; /// Velocidad a la cual camina
        unsigned int        _direccion; /// Dirección a la que el jugador está mirando
        sf::SoundBuffer     _buffer;  /// buffer para el sonido
        sf::Sound           _pasos;   /// canal utilizado por el buffer
        juegoProyectil&     _juego; /// instancia del juego utilizada para crear disparar proyectil
        unsigned int        _coolDown; /// tiempo de enfriamiento hasta que logre efectuan un nuevo disparo.
        Controller&         _controller; /// referencia de controller para saber cuál es el que le corresponde

    public:
        enum class Estados     {Quieto, Caminando};
        enum class Direcciones {Down, Left, Right, Up};
        //constructor
        personaje(int sprClase, int cantX, int cantY, sf::Vector2f frameActual, juegoProyectil& juego, Controller& controller);
        //sets
        void            setVelDesplaz(float velDesplaz);
        //gets
        sprite          getSpritePersonaje(); ///obtengo el objeto sprite
        float           getVelDesplaz();
        unsigned int    getDireccion();
        juegoProyectil& getJuegoActual(); /// retorna referencia la juego actual.
        //Métodos
        void            setSentidoX(int frame); /// Para conocer si está mirando hacia la izquierda o derecha.
        void            setSentidoY(int frame); /// Para conocer si está mirando hacia arriba o abajo
        void            animar(); /// pose de la animación.
        void            update(); /// Actualiza las físicas del jugador.
        void            disparar(); // método para disparar proyectil
        void            draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
        sf::FloatRect   getBounds() override;
};

