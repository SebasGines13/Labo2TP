#include <iostream>
#include "juego.h"

juego::juego(sf::Vector2u resolucion) 
{ //Constructor
	_ventana = new sf::RenderWindow(sf::VideoMode(resolucion.x, resolucion.y), "Dungeon ++ v0.6");
	_fps = 60;
	_ventana->setFramerateLimit(_fps);
	_gameOver = false;
	_mapa = new mapa(1, 16, 16, 50, 40); //Inicializo la variable dinámica para el mapa.
	_j1 = new personaje(11, 4, 4, sf::Vector2f(0, 0), *this, _controller); ///Inicilizo la variable dinámica de jugador.
	_j1->setPosition(sf::Vector2f(_mapa->getPlayerSpawn().x * _mapa->getTileWidth(), _mapa->getPlayerSpawn().y * _mapa->getTilHeight())); /// Ubico el personaje de acuerdo a spawn definido en el mapa.
	//_mago1 = new enemigo(sf::Vector2f(800, 400)); /// Inicializo la variable dinámica de jugador
	
	_music.openFromFile("audio/fondo.wav");
	_music.play();
	_music.setVolume(5.f);
	gameLoop();
}

void juego::gameLoop() 
{
	sf::Event event;
	while (_ventana->isOpen()) {
		while (_ventana->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				_ventana->close();
			}
		}
		command();
		update();
		draw();
	}
}

void juego::command()
{
	_controller.reset();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { /// Izquierda
		_controller.push(Controller::Buttons::Left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { /// Derecha
		_controller.push(Controller::Buttons::Right);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { /// Arriba
		_controller.push(Controller::Buttons::Up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { /// Abajo
		_controller.push(Controller::Buttons::Down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { /// Para disparar
		_controller.push(Controller::Buttons::ButtonShoot);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) { /// Para quitar la música
		_controller.push(Controller::Buttons::ButtonMute);
	}	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) { /// Para bajar música
		_controller.push(Controller::Buttons::ButtonLess);		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) { /// Para subir música
		_controller.push(Controller::Buttons::ButtonMore);
	}
}

void juego::update() 
{   ///Lógicas y reglas propias del juego.
	/// Actualiza las físicas del jugador.
	_j1->update();
	colisionConBloques();

	/// iterator para recorrer todo la lista de proyectiles y actualizarlos.
	std::list<proyectil>::iterator i = _proyectiles.begin(); 
	while (i != _proyectiles.end()) {
		proyectil& p = (*i);
		p.update();
		if (p.getPosition().x > _ventana->getSize().x) { /// si se pasa de la pantalla lo elimino de la lista
			i = _proyectiles.erase(i);
		}
		else {
			i++;
		}
	}
	/// Actualizo controles de música
	if (_controller.isPressed(Controller::Buttons::ButtonLess) && _music.getVolume() > 1.f) {
		_music.setVolume(_music.getVolume() - 1.f);
	} else if (_controller.isPressed(Controller::Buttons::ButtonMore) && _music.getVolume() < 50.f) {
		_music.setVolume(_music.getVolume() + 1.f);
	} else if (_controller.isPressed(Controller::Buttons::ButtonMute)) {
		if (_music.getStatus() == _music.Playing) {
			_music.pause();
		}
		else _music.play();
	}	
}

void juego::draw()
{	///Dibuja en pantalla los elementos.
	_ventana->clear(); ///Limpio la pantalla con lo que había antes.
	_ventana->draw(*_mapa); ///Dibujo el mapa
	_ventana->draw(*_j1); /// Dibujo el personaje.	
	for (proyectil& p : _proyectiles) { /// recorro con un for each la lista de proyectiles y las dibujo
		_ventana->draw(p);
	}
	_ventana->display();//Muestro la ventana.
}

void juego::crearProyectil(sf::Vector2f posicion) 
{
	static sf::SoundBuffer _bufferP;  /// buffer para el sonido
	static sf::Sound _sonido;   /// canal utilizado por el buffer
	_bufferP.loadFromFile("audio/proyectil.wav");
	_sonido.setBuffer(_bufferP);
	_sonido.setVolume(20.f);
	_sonido.setPitch(1.f);
	_sonido.play();
	_proyectiles.push_back(proyectil(posicion));
}

void juego::colisionConBloques() /// el juego evalua cuando el personaje colisiona con los bloques y qué hacer con él en caso de que sea sólido o no.
{
	const std::vector<bloque*>& bloques = _mapa->getBloques();
	for (bloque* pBloque : bloques) {
		if (pBloque->isSolid() && _j1->isCollision(*pBloque)) {
			if (_j1->getVelocidad().y > 0) {
				_j1->move(0, -(_j1->getBounds().top + _j1->getBounds().height - pBloque->getBounds().top));
			}
			else if (_j1->getVelocidad().y < 0) {
				_j1->move(0, (pBloque->getBounds().top + pBloque->getBounds().height - _j1->getBounds().top));
			}
			else if (_j1->getVelocidad().x > 0) {
				_j1->move(-(_j1->getBounds().left + _j1->getBounds().width - pBloque->getBounds().left), 0);
			}
			else if (_j1->getVelocidad().x < 0) {
				_j1->move((pBloque->getBounds().left + pBloque->getBounds().width - _j1->getBounds().left), 0);
			}
		}
	}
}
