#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "sprite.h"
#include "juegoProyectil.h"
using namespace sf;

enum class Estados{QUIETO, CAMINANDO, MUERTO};
//enum class Direcciones{ABAJO = 0, IZQUIERDA = 1, DERECHA = 2, ARRIBA = 3, IZQABAJO = 4, DERABAJO = 5, IZQARRIBA = 6, DERARRIBA = 7};
const int ABAJO=0, IZQUIERDA=1, DERECHA=2, ARRIBA=3, IZQABAJO=4, DERABAJO=5, IZQARRIBA=6, DERARRIBA=7;

class personaje
{
    private:
        sprite              *_sprPersonaje; /// Composición del objeto con propiedades y métodos propios para el manejo de sprites.
        Estados             _estado; /// enum para chequear estados, como por ejemplo si el jugador está caminando o no.
        Vector2f            _velocidad; /// Velocidad actual o posición donde se encuentra
        float               _velDesplaz; /// Velocidad a la cual camina
        int                 _direccion; /// Dirección a la que el jugador está mirando
        SoundBuffer         _buffer;  /// buffer para el sonido
        Sound               _pasos;   /// canal utilizado por el buffer
        juegoProyectil&     _juego; /// instancia del juego utilizada para crear disparar proyectil
        unsigned int        _coolDown; /// tiempo de enfriamiento hasta que logre efectuan un nuevo disparo.
    public:
        //constructor
        personaje(int sprClase, int cantX, int cantY, Vector2f frameActual, juegoProyectil& juego);
        //sets
        void    setPosicion(Vector2f position); //Setea la posición del jugador a un determinado punto x e y
        void    setEstado(Estados estado);
        void    setVelocidad(Vector2f velocidad);
        void    setVelDesplaz(float velDesplaz);
        void    setDireccion(int direccion);
        void    setCoolDown(unsigned int coolDown);
        //gets
        sprite          getSpritePersonaje(); ///obtengo el objeto sprite
        Vector2f        getPosicion(); ///Devuelve la posición del jugador
        Estados         getCaminando();
        Vector2f        getVelocidad();
        float           getVelDesplaz();
        int             getDireccion();
        juegoProyectil& getJuegoActual(); /// retorna referencia la juego actual.
        unsigned int    getCoolDown();

        //Métodos
        void    setSentidoX(int frame); /// Para conocer si está mirando hacia la izquierda o derecha.
        void    setSentidoY(int frame); /// Para conocer si está mirando hacia arriba o abajo
        void    animar(); /// pose de la animación.
        void    mover(Vector2f movimiento); /// Mueve al jugador de acuerdo a la velocidad del mismo.
        void    update(Vector2f velocidad); /// Actualiza las físicas del jugador.
        void    actualizaVelocidad(Vector2f velocidad); /// actualiza la posición del jugador de acuerdo a su dirección.
        void    disparar(); // método para disparar proyectil
};

