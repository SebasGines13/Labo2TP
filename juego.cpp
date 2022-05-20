#include "juego.h"

juego::juego(sf::Vector2u resolucion) { //Constructor
	_ventana = new sf::RenderWindow(sf::VideoMode(resolucion.x, resolucion.y), "Dungeon ++ v0.5");
	_ventana->setFramerateLimit(_fps);
	inicializar();
	gameLoop();
}


void juego::inicializar() { ///Inicializa las variables y diferentes aspectos.
	_gameOver = false;
	_j1 = new personaje(2,6,4, sf::Vector2f(0,0), *this); ///Inicilizo la variable din�mica de jugador.
	//_j1 = new personaje(11,4,4,Vector2f(0,0)); ///Inicilizo la variable din�mica de jugador.
	_mago1 = new enemigo(sf::Vector2f(800,400)); /// Inicializo la variable din�mica de jugador
	_mapa = new mapa(1,16,16,48,64); //Inicializo la variable din�mica para el mapa.
	_evento = new sf::Event(); ///Inicializo la variable din�mica del evento.
	_music.openFromFile("audio/fondo.wav");
	_music.play();
	_music.setVolume(5.f);	
}


void juego::procesarEventos() { ///Interacci�n con el usuario, bien sea mouse, teclado, etc.
	switch (_evento->type){
		case sf::Event::Closed: ///Para que se pueda presionar sobre la cruz y se cierre la ventana.
			exit(1);
		break;
		/// 
		///					PRESIONAR TECLA
		///
		case sf::Event::KeyPressed: ///Verifica si existe una tecla presionada
			if (_evento->key.code == sf::Keyboard::A) {
				_teclasJugador[IZQUIERDA] = true;
			}
			else if (_evento->key.code == sf::Keyboard::D) {
				_teclasJugador[DERECHA] = true;
			}
			else if (_evento->key.code == sf::Keyboard::W) {
				_teclasJugador[ARRIBA] = true;
			}
			else if (_evento->key.code == sf::Keyboard::S) {
				_teclasJugador[ABAJO] = true;			
			}
			
			else if (_evento->key.code == sf::Keyboard::M) { /// Para quitar la m�sica
				if (_music.getStatus() == _music.Playing) {
					_music.pause();					
				}
				else _music.play();
			}
			else if (_evento->key.code == sf::Keyboard::Subtract) { /// Para bajar m�sica
				if (_music.getVolume() > 1) {
					_music.setVolume(_music.getVolume() - 1.f);
				}			
			}
			else if (_evento->key.code == sf::Keyboard::Add) { /// Para subir m�sica
				if (_music.getVolume() < 50.f) {
					_music.setVolume(_music.getVolume() + 1.f);
				}				
			}
			
			
		break;
		/// 
		///					SOLTAR TECLA
		///
		case Event::KeyReleased: ///Verifica si es que se suelta la tecla
			if (_evento->key.code == sf::Keyboard::A) {
				_teclasJugador[IZQUIERDA] = false;
				_j1->setSentidoX(0); /// Para que al soltar, se establezca el primer sprite de cada fila
			}
			else if (_evento->key.code == sf::Keyboard::D) {
				_teclasJugador[DERECHA] = false;
				_j1->setSentidoX(0); /// Para que al soltar, se establezca el primer sprite de cada fila
			}
			else if (_evento->key.code == sf::Keyboard::W) {
				_teclasJugador[ARRIBA] = false;
				_j1->setSentidoX(0); /// Para que al soltar, se establezca el primer sprite de cada fila
			}
			else if (_evento->key.code == sf::Keyboard::S) {
				_teclasJugador[ABAJO] = false;
				_j1->setSentidoX(0); /// Para que al soltar, se establezca el primer sprite de cada fila
			}
			else if (_evento->key.code == sf::Keyboard::Space && _j1->getCoolDown() == 0) { /// Para disparar
				_j1->disparar();
			}
		break;
	}
	if (_j1->getCoolDown() > 0) {
		_j1->setCoolDown(_j1->getCoolDown() - 1);
	}
} 

void juego::procesarLogica() { ///L�gicas y reglas propias del juego.
	///Chequeo las teclas
	_j1->setEstado(Estados::QUIETO); // inicio con el jugador asumi�ndolo como que no est� caminando.
	if (_teclasJugador[IZQUIERDA]) {
		_j1->setEstado(Estados::CAMINANDO); // jugador comienza a caminar
		if (_teclasJugador[ARRIBA]) {
			_j1->setDireccion(IZQARRIBA);
		}
		else if(_teclasJugador[ABAJO]) {
			_j1->setDireccion(IZQABAJO);
		}
		else {
			_j1->setDireccion(IZQUIERDA);
		}
	}
	else if (_teclasJugador[DERECHA]) {
		_j1->setEstado(Estados::CAMINANDO); // jugador comienza a caminar
		if (_teclasJugador[ARRIBA]) {
			_j1->setDireccion(DERARRIBA);			
		}
		else if (_teclasJugador[ABAJO]) {
			_j1->setDireccion(DERABAJO);
		}
		else {
			_j1->setDireccion(DERECHA);
		}
	}
	else if (_teclasJugador[ARRIBA]) {
		_j1->setEstado(Estados::CAMINANDO); // jugador comienza a caminar
		_j1->setDireccion(ARRIBA);
	}
	else if (_teclasJugador[ABAJO]) {
		_j1->setEstado(Estados::CAMINANDO); // jugador comienza a caminar
		_j1->setDireccion(ABAJO);
	}

	/// Selecciono la velocidad (hacia donde se va a evaluar si el jugador puede dirigirse)
	proximaPosicion();

	/// Actualiza las f�sicas del jugador.

	if (!existeColision()) { /// si no tiene colisi�n, se actualiza la posici�n del jugador.
		_j1->update(_velocidadAux);
	}

	std::list<proyectil>::iterator i = _proyectiles.begin(); /// iterator para recorrer todo la lista de proyectiles
	while (i != _proyectiles.end()) {
		proyectil& p = (*i);
		p.update();
		if (p.getSprite().getPosicion().x > 950) { /// si se pasa de la pantalla lo elimino de la lista
			i = _proyectiles.erase(i);
		}
		else {
			i++;
		}
	}
	
}

void juego::proximaPosicion() {
	switch (_j1->getDireccion())
	{
	case ABAJO:
		_velocidadAux = sf::Vector2f(0, _j1->getVelDesplaz());
		_posicionAux = _j1->getPosition() + _velocidadAux;
		break;
	case IZQABAJO:
		_velocidadAux = sf::Vector2f(-_j1->getVelDesplaz(), _j1->getVelDesplaz());
		_posicionAux = _j1->getPosition() + _velocidadAux;
		break;
	case DERABAJO:
		_velocidadAux = sf::Vector2f(_j1->getVelDesplaz(), _j1->getVelDesplaz());
		_posicionAux = _j1->getPosition() + _velocidadAux;
		break;
	case IZQUIERDA:
		_velocidadAux = sf::Vector2f(-_j1->getVelDesplaz(), 0);
		_posicionAux = _j1->getPosition() + _velocidadAux;
		break;
	case DERECHA:
		_velocidadAux = sf::Vector2f(_j1->getVelDesplaz(), 0);
		_posicionAux = _j1->getPosition() + _velocidadAux;
		break;
	case ARRIBA:
		_velocidadAux = sf::Vector2f(0, -_j1->getVelDesplaz());
		_posicionAux = _j1->getPosition() + _velocidadAux;
		break;
	case IZQARRIBA:
		_velocidadAux = sf::Vector2f(-_j1->getVelDesplaz(), -_j1->getVelDesplaz());
		_posicionAux = _j1->getPosition() + _velocidadAux;
		break;
	case DERARRIBA:
		_velocidadAux = sf::Vector2f(_j1->getVelDesplaz(), -_j1->getVelDesplaz());
		_posicionAux = _j1->getPosition() + _velocidadAux;
		break;
	}
}

bool juego::existeColision()
{
	if (_mapa->existeBloqueo(_posicionAux)) {
		return true;
	}
	return false;
}

void juego::gameLoop() {
	while (!_gameOver) {
			while (_ventana->pollEvent(*_evento)) {
				procesarEventos();					
			}		
			procesarLogica();
			dibujar();
		}	
}

void juego::dibujar() { ///Dibuja en pantalla los elementos.
	_ventana->clear(); ///Limpio la pantalla con lo que hab�a antes.
	_ventana->draw(*_mapa); ///Dibujo el mapa	
	_ventana->draw(*_j1); /// Dibujo el personaje.	
	for (proyectil& p : _proyectiles) { /// recorro con un for each la lista de proyectiles y las dibujo
		_ventana->draw(p);
	}
	_ventana->draw(_mago1->getSprite().getSprite());
	_ventana->display(); //Muestro la ventana.
}

void juego::crearProyectil(Vector2f posicion)
{

	static SoundBuffer _bufferP;  /// buffer para el sonido
	static Sound _sonido;   /// canal utilizado por el buffer
	_bufferP.loadFromFile("audio/proyectil.wav");
	_sonido.setBuffer(_bufferP);
	_sonido.setVolume(20.f);
	_sonido.setPitch(1.f);
	_sonido.play();
	_proyectiles.push_back(proyectil(posicion));
}