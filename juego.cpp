#include "juego.h"

juego::juego(Vector2u resolucion) { //Constructor
	_ventana = new RenderWindow(VideoMode(resolucion.x, resolucion.y), "Moquitos v0.3");
	inicializar();
	gameLoop();
}


void juego::inicializar() { ///Inicializa las variables y diferentes aspectos.
	_gameOver = false;
	_j1 = new personaje(11,4,4,Vector2i(0,0)); ///Inicilizo la variable dináminca de jugador.	
	_evento = new Event(); ///Inicializo la variable dinámica del evento.
	_fps = 60; /// 60 frames por segundo
	_reloj1 = new Clock(); /// reloj para que junto con el cronómetro, pueda medir el tiempo transcurrido.
	_cronometro1 = new Time(); ///Ver reloj.
}


void juego::dibujar() { ///Dibuja en pantalla los elementos.
	_ventana->clear(); ///Limpio la pantalla con lo que había antes.
	_ventana->draw(_j1->getSpritePersonaje().getSprite());
	_ventana->display(); //Muestro la ventana.
} 


void juego::procesarEventos() { ///Interacción con el usuario, bien sea mouse, teclado, etc.
	switch (_evento->type){
		case Event::Closed: ///Para que se pueda presionar sobre la cruz y se cierre la ventana.
			exit(1);
		break;
		/// 
		///					PRESIONAR TECLA
		///
		case Event::KeyPressed: ///Verifica si existe una tecla presionada
			if (_evento->key.code == Keyboard::A) {
				_teclasJugador[IZQUIERDA] = true;
			}
			else if (_evento->key.code == Keyboard::D) {
				_teclasJugador[DERECHA] = true;
			}
			else if (_evento->key.code == Keyboard::W) {
				_teclasJugador[ARRIBA] = true;
			}
			else if (_evento->key.code == Keyboard::S) {
				_teclasJugador[ABAJO] = true;			
			}
		break;
		/// 
		///					SOLTAR TECLA
		///
		case Event::KeyReleased: ///Verifica si es que se suelta la tecla
			if (_evento->key.code == Keyboard::A) {
				_teclasJugador[IZQUIERDA] = false;
			}
			else if (_evento->key.code == Keyboard::D) {
				_teclasJugador[DERECHA] = false;
			}
			else if (_evento->key.code == Keyboard::W) {
				_teclasJugador[ARRIBA] = false;
			}
			else if (_evento->key.code == Keyboard::S) {
				_teclasJugador[ABAJO] = false;
			}
		break;
	}
} 

void juego::procesarLogica() { ///Lógicas y reglas propias del juego.
	///Chequeo las teclas
	_j1->setEstado(Estados::QUIETO); // inicio con el jugador asumiéndolo como que no está caminando.
	if (_teclasJugador[IZQUIERDA]) {
		_j1->setEstado(Estados::CAMINANDO); // jugador comienza a caminar
		if (_teclasJugador[ARRIBA]) {
			_j1->setDireccion(IZQARRIBA);
		}
		else if(_teclasJugador[ABAJO]) {
			_j1->setDireccion(IZQABAJO);
		}
		else _j1->setDireccion(IZQUIERDA);
	}
	else if (_teclasJugador[DERECHA]) {
		_j1->setEstado(Estados::CAMINANDO); // jugador comienza a caminar
		if (_teclasJugador[ARRIBA]) {
			_j1->setDireccion(DERARRIBA);
		}
		else if (_teclasJugador[ABAJO]) {
			_j1->setDireccion(DERABAJO);
		}
		else _j1->setDireccion(DERECHA);
	}
	else if (_teclasJugador[ARRIBA]) {
		_j1->setEstado(Estados::CAMINANDO); // jugador comienza a caminar
		_j1->setDireccion(ARRIBA);
	}
	else if (_teclasJugador[ABAJO]) {
		_j1->setEstado(Estados::CAMINANDO); // jugador comienza a caminar
		_j1->setDireccion(ABAJO);
	}
	/// Actualiza las físicas del jugador.
	_j1->update(); 
}

void juego::gameLoop() {
	while (!_gameOver) {
		*_cronometro1 = _reloj1->getElapsedTime(); /// Obtenemos el tiempo transcurrido
		if (_cronometro1->asSeconds() > 1 / _fps) { /// Tiempo a esperar para que se ejecute el siguiente evento.
			while (_ventana->pollEvent(*_evento)) {
				procesarEventos();	
			}						
			procesarLogica();
			dibujar();
			_reloj1->restart(); /// Como es acumulativo el tiempo, tengo que reiniciarlo para que se pueda evaluar un nuevo evento.
		}	
	}
}