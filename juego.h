#pragma once
#include <SFML/Graphics.hpp>
#include "personaje.h"
#include "mapa.h"
using namespace sf;

class juego
{ 
    private:
        RenderWindow* _ventana;  ///Ventana donde se va a mostrar el juego.
        bool          _gameOver;  ///Booleano que controla si se terminó el juego.
        personaje*    _j1;          ///Objeto de clase personaje.
        mapa*         _mapa;          ///Objeto de la clase mapa.
        Event*        _evento;          /// Evento es todo aquello que suceda durante el juego.
        Clock*        _reloj1;
        Time*         _cronometro1;
        int           _fps;
        bool          _teclasJugador[4];  /// Izquierda, derecha, arriba y abajo.
        Music         _music;    /// música de fondo
    public:
        //Constructor
        juego(Vector2u resolucion); 
        //Métodos
        void inicializar(); ///Inicializa las variables y aspectos.
        void dibujar(); ///Dibuja en pantalla los elementos.
        void procesarLogica(); ///Lógicas y reglas propias del juego.
        void procesarEventos();
        void gameLoop();
};
