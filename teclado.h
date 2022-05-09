#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class teclado
{
	private:
		teclado();				/// Constructor
		Event* _evento;          /// Evento es todo aquello que suceda durante el juego.
		bool _teclasJugador[4];  /// Izquierda, derecha, arriba y abajo.
		void procesarEventos();
	public:
		static teclado* getTeclado(); /// se crea el objeto de tipo singleton, ya que voy a necesitar que sea uno solo accesible por todos.
		bool* getTeclasJugador();
		void setTeclasJugador();
};

