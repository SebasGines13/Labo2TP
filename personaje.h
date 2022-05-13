#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "sprite.h"
using namespace sf;

enum class Estados{QUIETO, CAMINANDO, MUERTO};
//enum class Direcciones{ABAJO = 0, IZQUIERDA = 1, DERECHA = 2, ARRIBA = 3, IZQABAJO = 4, DERABAJO = 5, IZQARRIBA = 6, DERARRIBA = 7};
const int ABAJO=0, IZQUIERDA=1, DERECHA=2, ARRIBA=3, IZQABAJO=4, DERABAJO=5, IZQARRIBA=6, DERARRIBA=7;

class personaje
{
    private:
        sprite      *_sprPersonaje; /// Composici�n del objeto con propiedades y m�todos propios para el manejo de sprites.
        Estados     _estado; /// enum para chequear estados, como por ejemplo si el jugador est� caminando o no.
        Vector2f    _velocidad; /// Velocidad actual o posici�n donde se encuentra
        float       _velDesplaz; /// Velocidad a la cual camina
        int         _direccion; /// Direcci�n a la que el jugador est� mirando
        SoundBuffer _buffer;  /// buffer para el sonido
        Sound       _pasos;   /// canal utilizado por el buffer
    public:
        //constructor
        personaje(int sprClase, int cantX, int cantY, Vector2f frameActual);
        //sets
        void    setPosicion(Vector2f position); //Setea la posici�n del jugador a un determinado punto x e y
        void    setEstado(Estados estado);
        void    setVelocidad(Vector2f velocidad);
        void    setVelDesplaz(float velDesplaz);
        void    setDireccion(int direccion);
        //gets
        sprite      getSpritePersonaje(); ///obtengo el objeto sprite
        Vector2f    getPosicion(); ///Devuelve la posici�n del jugador
        Estados     getCaminando();
        Vector2f    getVelocidad();
        float       getVelDesplaz();
        int         getDireccion();
        //M�todos
        void    setSentidoX(int frame); /// Para conocer si est� mirando hacia la izquierda o derecha.
        void    setSentidoY(int frame); /// Para conocer si est� mirando hacia arriba o abajo
        void    animar(); /// pose de la animaci�n.
        void    mover(Vector2f movimiento); /// Mueve al jugador de acuerdo a la velocidad del mismo.
        void    update(); /// Actualiza las f�sicas del jugador.
        void    seleccionarVelocidad(); /// Para que actualice la velocidad de acuerdo a la direcci�n que se encuentre.

};

