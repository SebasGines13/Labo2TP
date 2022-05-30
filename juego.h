#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Personaje.h"
#include "Mapa.h"
#include "Proyectil.h"
#include "JuegoProyectil.h"
#include "Enemigo.h"
#include "Controller.h"
#include "Menu.h"
#include <list>

class Juego: public JuegoProyectil
{ 
    private:
        sf::RenderWindow*       _ventana;  ///Ventana donde se va a mostrar el juego.
        bool                    _gameOver;  ///Booleano que controla si se terminó el juego.
        Personaje*              _j1;          ///Objeto de clase personaje.
        Mapa*                   _mapa;          ///Objeto de la clase mapa.
        int                     _fps;      /// utilizado para limitar los frames
        sf::Music               _music;    /// música de fondo
        std::list<Proyectil>    _proyectiles; /// lista de proyectiles
        Controller              _controller; /// controles asociados al jugador
        Menu*                   _menu; /// para el menú del juego.
        bool                    _primerIngreso; /// para validar si es el primer ingreso y mostrar la pantalla de controles
    public:
        //Constructor
        Juego(sf::Vector2u resolucion);
        //Métodos     
        void gameLoop();
        void command(); /// para verificar las teclas.
        void update(); ///Lógicas y reglas propias del juego.
        void draw(); ///Dibuja en pantalla los elementos.
        void crearProyectil(sf::Vector2f posicion) override; /// Para que disparar un proyectil
        void colisionConBloques();
};
