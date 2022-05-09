#include "teclado.h"


teclado::teclado() {

}

teclado* teclado::getTeclado() {
	static teclado tecla;
	return &tecla;
}

void teclado::procesarEventos() { ///Interacción con el usuario, bien sea mouse, teclado, etc.
	switch (evento->type) {
	case Event::Closed: ///Para que se pueda presionar sobre la cruz y se cierre la ventana.
		exit(1);
		break;
		/// 
		///					PRESIONAR TECLA
		///
	case Event::KeyPressed: ///Verifica si existe una tecla presionada
		if (evento->key.code == Keyboard::A) {
			teclasJugador[IZQUIERDA] = true;
		}
		else if (evento->key.code == Keyboard::D) {
			teclasJugador[DERECHA] = true;
		}
		else if (evento->key.code == Keyboard::W) {
			teclasJugador[ARRIBA] = true;
		}
		else if (evento->key.code == Keyboard::S) {
			teclasJugador[ABAJO] = true;
		}
		break;
		/// 
		///					SOLTAR TECLA
		///
	case Event::KeyReleased: ///Verifica si es que se suelta la tecla
		if (evento->key.code == Keyboard::A) {
			teclasJugador[IZQUIERDA] = false;
		}
		else if (evento->key.code == Keyboard::D) {
			teclasJugador[DERECHA] = false;
		}
		else if (evento->key.code == Keyboard::W) {
			teclasJugador[ARRIBA] = false;
		}
		else if (evento->key.code == Keyboard::S) {
			teclasJugador[ABAJO] = false;
		}
		break;
	}
}

bool* getTeclasJugador() {
	return _teclasJugador;
}
void setTeclasJugador();