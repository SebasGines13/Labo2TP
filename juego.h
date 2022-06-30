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
        //M�todos     
        void gameLoop();
        void command(); /// para verificar las teclas.
        void update(); ///L�gicas y reglas propias del juego.
        void draw(); ///Dibuja en pantalla los elementos.
        void updateMusic();  /// Actualizo controles de m�sica.
        void PrepararJuego(int modo);
        void crearProyectil(sf::Vector2f posicion) override; /// Para que disparar un proyectil
        void colisionesJugadorBloques();
        void colisionesJugadorItem();
        void colisionesProyectilBloques();
        void colisionesEnemigo();
        bool colisionConBloques(Proyectil& p);
        void colisionConBloques(Enemigo& e);
        bool colisionProyectilEnemigo(Enemigo& e);
        void grabarPuntaje();
        void ranking();
        void configuracion();
        void coolDowns();
        void spawnJefe();
        void crearEnemigo();
        void avanzarNivel();
        void ganarJuego();
    private:
        enum class coolDown { Enemigo, ItemPantalla, Menu };
        sf::RenderWindow*       _ventana;       /// Ventana donde se va a mostrar el juego.
        bool                    _gameOver;      /// Booleano que controla si se termin� el juego.
        Jugador*                _j1;           /// Objeto de clase personaje.
        Mapa*                   _mapa;            /// Objeto de la clase mapa.
        int                     _fps;           /// utilizado para limitar los frames
        sf::Music               _music;         /// m�sica de fondo
        std::list<Proyectil*>   _proyectiles;   /// lista de proyectiles
        std::list<Enemigo*>     _enemigos;      /// lista de enemigos
        Controller              _controller;    /// controles asociados al jugador
        Menu*                   _menu;                /// para el men� del juego.
        bool                    _bienvenidaAjuego; /// para validar si es el primer ingreso al juego y mostrar la pantalla de controles y camino del dungeon.
        bool                    _juegoGanado;    /// si el jugador gan� el juego.
        bool                    _pasoNivel;      // si el jugador paso de nivel.
        GUI*                    _gui;           /// para controlar y mostrar elementos varios de juego como ser la vida y el puntaje.
        int                     _coolDown[3];   /// Cooldown varios, como el de respawn de enemigos, items, del efecto de lastimado, etc.
        Listado*                _listado;       /// Objeto para el manejo de listados.
        Configuracion*          _configuracion;
        int                     _dificultad;    /// Dificultad del juego
        int                     _coolDownEnemigos;
        int                     _nroJefeActual;  /// Vector de estados de jefes.
        int                     _nivelMapa; /// nivel del mapa
        const int               COOLDOWNJUGADORLASTIMADO = 60;
        const int               COOLDOWNENEMIGOLASTIMADO = 30;
        const int               COOLDOWNMENU = 200;
        const int               COOLDOWNITEMPANTALLA = 180;
        const int               TIEMPOJEFE = 10;
};
