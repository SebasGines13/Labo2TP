#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "personaje.h"
#include "mapa.h"
#include "proyectil.h"
#include "juegoProyectil.h"
#include "enemigo.h"
#include <list>

class juego: public juegoProyectil
{ 
    private:
        sf::RenderWindow*       _ventana;  ///Ventana donde se va a mostrar el juego.
        bool                    _gameOver;  ///Booleano que controla si se terminó el juego.
        personaje*              _j1;          ///Objeto de clase personaje.
        enemigo*                _mago1;         ///Objeto de clase enemigo.
        mapa*                   _mapa;          ///Objeto de la clase mapa.
        sf::Event*              _evento;          /// Evento es todo aquello que suceda durante el juego.
        int                     _fps = 60;      /// utilizado para limitar los frames
        bool                    _teclasJugador[4];  /// Izquierda, derecha, arriba y abajo.
        sf::Music               _music;    /// música de fondo
        sf::Vector2f            _velocidadAux; /// variable auxiliar para el próximo paso del jugador y que se calcula antes de actualizarlo.
        sf::Vector2f            _posicionAux; /// variable auxiliar para el próximo paso del jugador y que se calcula antes de actualizarlo.
        std::list<proyectil>    _proyectiles; /// lista de proyectiles
    public:
        //Constructor
        juego(sf::Vector2u resolucion);
        //Métodos
        void inicializar(); ///Inicializa las variables y aspectos.
        void dibujar(); ///Dibuja en pantalla los elementos.
        void procesarLogica(); ///Lógicas y reglas propias del juego.
        void procesarEventos();
        void gameLoop();
        void proximaPosicion(); /// Para que actualice la velocidad de acuerdo a la dirección que se encuentre.
        bool existeColision(); /// Verifica si es válida la posición (_velocidadAux) a la cual quiere dirigirse el jugador.
        void crearProyectil(sf::Vector2f posicion) override; /// Para que disparar un proyectil
};
