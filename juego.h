#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <time.h>
#include "Personaje.h"
#include "Mapa.h"
#include "Proyectil.h"
#include "JuegoProyectil.h"
#include "Enemigo.h"
#include "Jugador.h"
#include "Controller.h"
#include "Menu.h"
#include "GUI.h"
#include "Ranking.h"
#include "Listado.h"
#include "Configuracion.h"


class Juego: public JuegoProyectil
{ 
    public:
        //Constructor
        Juego(sf::Vector2u resolucion);
        //Destructor
        ~Juego();
        //Métodos     
        void gameLoop();
        void command(); /// para verificar las teclas.
        void update(); ///Lógicas y reglas propias del juego.
        void draw(); ///Dibuja en pantalla los elementos.
        void updateMusic();  /// Actualizo controles de música.
        void reiniciarJuego(); /// Reinicia los valores del jugador.
        void crearProyectil(sf::Vector2f posicion) override; /// Para que disparar un proyectil
        void colisionesJugadorBloques();
        void colisionesJugadorItem();
        void colisionesProyectilBloques();
        void colisionesEnemigoBloques();
        bool colisionConBloques(Proyectil& p);
        void colisionConBloques(Enemigo& e);
        bool colisionProyectilEnemigo(Enemigo& e);
        void grabarPuntaje();
        void ranking();
        void configuracion();
        void coolDowns();
    private:
        enum class coolDown { Lastimado, Enemigo, ItemPantalla, Menu };
        sf::RenderWindow*       _ventana;       /// Ventana donde se va a mostrar el juego.
        bool                    _gameOver;      /// Booleano que controla si se terminó el juego.
        Jugador*                _j1;           /// Objeto de clase personaje.
        Mapa*                   _mapa;            /// Objeto de la clase mapa.
        int                     _fps;           /// utilizado para limitar los frames
        sf::Music               _music;         /// música de fondo
        std::list<Proyectil*>   _proyectiles;   /// lista de proyectiles
        std::list<Enemigo*>     _enemigos;      /// lista de enemigos
        Controller              _controller;    /// controles asociados al jugador
        Menu*                   _menu;                /// para el menú del juego.
        bool                    _bienvenidaAjuego; /// para validar si es el primer ingreso al juego y mostrar la pantalla de controles y camino del dungeon.
        GUI*                    _gui;           /// para controlar y mostrar elementos varios de juego como ser la vida y el puntaje.
        int                     _coolDown[4];   /// Cooldown varios, como el de respawn de enemigos, items, del efecto de lastimado, etc.
        Listado*                _listado;       /// Objeto para el manejo de listados.
        Configuracion*          _configuracion;
        int                     _dificultad;    /// Dificultad del juego
        int                     coolDownEnemigos;
        const int               COOLDOWNLASTIMADO = 60;
        const int               COOLDOWNMENU = 200;
        const int               COOLDOWNITEMPANTALLA = 120;
};
