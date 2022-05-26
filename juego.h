#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "personaje.h"
#include "mapa.h"
#include "proyectil.h"
#include "juegoProyectil.h"
#include "enemigo.h"
#include "Controller.h"
#include <list>

class juego: public juegoProyectil
{ 
    private:
        sf::RenderWindow*       _ventana;  ///Ventana donde se va a mostrar el juego.
        bool                    _gameOver;  ///Booleano que controla si se terminó el juego.
        personaje*              _j1;          ///Objeto de clase personaje.
        mapa*                   _mapa;          ///Objeto de la clase mapa.
        int                     _fps;      /// utilizado para limitar los frames
        sf::Music               _music;    /// música de fondo
        std::list<proyectil>    _proyectiles; /// lista de proyectiles
        Controller              _controller; /// controles asociados al jugador
    public:
        //Constructor
        juego(sf::Vector2u resolucion);
        //Métodos     
        void gameLoop();
        void command(); /// para verificar las teclas.
        void update(); ///Lógicas y reglas propias del juego.
        void draw(); ///Dibuja en pantalla los elementos.
        void crearProyectil(sf::Vector2f posicion) override; /// Para que disparar un proyectil
        void colisionConBloques();
};
