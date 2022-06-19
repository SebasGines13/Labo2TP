#include <iostream>
#include "Juego.h"

Juego::Juego(sf::Vector2u resolucion)
{ //Constructor
	_ventana = new sf::RenderWindow(sf::VideoMode(resolucion.x, resolucion.y), "Dungeon ++ v0.9");
	_fps = 60;
	_ventana->setFramerateLimit(_fps);
	_gameOver = false;
	_mapa = new Mapa(1, 16, 16, 50, 40); //Inicializo la variable dinámica para el mapa.
	_j1 = new Jugador(1, *this, _controller); ///Inicilizo la variable dinámica de jugador.
	_j1->setPosition(sf::Vector2f(_mapa->getPlayerSpawn())); /// Ubico el personaje de acuerdo a spawn definido en el mapa.
	_music.openFromFile("audio/fondo.wav");
	_music.play();
	_music.setVolume(10.f);
	_menu = new Menu();
	_primerIngreso = true;
	srand(time(NULL));
	int i = rand() % 3;
	_enemigos.push_back(new Enemigo(11,sf::Vector2f(_mapa->getEnemigoSpawn(i))));
	_coolDown[(int)coolDown::Lastimado] = COOLDOWNLASTIMADO;
	_coolDown[(int)coolDown::Enemigo] = COOLDOWNENEMIGOS;
	_coolDown[(int)coolDown::Menu] = COOLDOWNMENU;
	gameLoop();
}

Juego::~Juego()
{
	delete _ventana;
	delete _j1;
	delete _mapa;
	delete _menu;
}


void Juego::gameLoop()
{
	sf::Event event;
	while (_ventana->isOpen() && !_gameOver) {
		while (_ventana->pollEvent(event) ) {
			if (event.type == sf::Event::Closed) {
				_ventana->close();
			}
			else {
				_menu->command();
			}
		}		
		_menu->update();
		if (_menu->getOpcMenuPress()[(int)Menu::OpcMenu::Play]) {
			if (_primerIngreso) { // evalua si es el primer ingreso para mostrar luego la imagen de controles
				do {
					_primerIngreso = false; 
					_ventana->clear();
					_menu->getSprFuego()->animar();
					_ventana->draw(_menu->getSprFondo());
					_ventana->draw(_menu->getSprControles());					
					_ventana->draw(*_menu->getSprFuego());
					_ventana->display();
				} while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
				_menu->getSonidoTeclas().play();
				_menu->getSprCamino().setPosition((sf::Vector2f(_menu->getSprCamino().getGlobalBounds().width/2, _menu->getSprCamino().getGlobalBounds().height/2))); // para que luego pueda aplicar correctamente el efecto de zoom y avanzar en el camino de la mazmorra
				for (int i = 1; i < COOLDOWNMENU; i++) {
					_ventana->clear();
					_menu->getSprCamino().setScale(sf::Vector2f(1+(i/60.f), 1+(i/60.f)));
					_ventana->draw(_menu->getSprCamino());
					_ventana->display();
				}
			}
			command();
			update();
			draw();
		}
		else if (_menu->getOpcMenuPress()[(int)Menu::OpcMenu::Exit]) {
			_gameOver = true;
		}
		else if (_menu->getOpcMenuPress()[(int)Menu::OpcMenu::Ranking]) {

		}
		else if (_menu->getOpcMenuPress()[(int)Menu::OpcMenu::Config]) {

		}
		else if (_menu->getOpcMenuPress()[(int)Menu::OpcMenu::Credit]) {

		}
		else {
			_ventana->clear();
			_ventana->draw(*_menu);
			_ventana->display();
		}
	}
}

void Juego::command()
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

void Juego::update()
{   ///Lógicas y reglas propias del juego.
	_j1->update();
	colisionesPersonaje(); 
	colisionesProyectil();
	colisionesEnemigo();

	_coolDown[(int)coolDown::Lastimado] --; /// para evaluar si está lastimado el personaje
	if (_coolDown[(int)coolDown::Lastimado] == 0) {
		_coolDown[(int)coolDown::Lastimado] = COOLDOWNLASTIMADO;
		_j1->setLastimado(false);
	}

	_coolDown[(int)coolDown::Enemigo] --; /// para evaluar el respawn de enemigos
	if (_coolDown[(int)coolDown::Enemigo] == 0) {
		int i = rand() % 3;
		_enemigos.push_back(new Enemigo(11,sf::Vector2f(_mapa->getEnemigoSpawn(i))));
		_coolDown[(int)coolDown::Enemigo] = COOLDOWNENEMIGOS;
	}	
	updateMusic();
}

void Juego::draw()
{	///Dibuja en pantalla los elementos.
	_ventana->clear(); ///Limpio la pantalla con lo que había antes.
	_ventana->draw(*_mapa); ///Dibujo el mapa
	_ventana->draw(*_j1); /// Dibujo el personaje.	
	for (Enemigo *e : _enemigos) { /// recorro con un for each la lista de enemigos y los dibujo
		_ventana->draw(*e);
	}
	for (Proyectil *p : _proyectiles) { /// recorro con un for each la lista de proyectiles y las dibujo
		_ventana->draw(*p);
	}
	_ventana->display();//Muestro la ventana.
}

void Juego::crearProyectil(sf::Vector2f posicion)
{
	static sf::SoundBuffer _bufferP;  /// buffer para el sonido
	static sf::Sound _sonido;   /// canal utilizado por el buffer
	_bufferP.loadFromFile("audio/proyectil.wav");
	_sonido.setBuffer(_bufferP);
	_sonido.setVolume(20.f);
	_sonido.setPitch(1.f);
	_sonido.play();
	_proyectiles.push_back(new Proyectil(posicion));
}

void Juego::colisionesPersonaje() /// el juego evalua cuando el personaje colisiona con los bloques y qué hacer con él en caso de que sea sólido.
{
	const std::vector<Bloque*>& bloques = _mapa->getBloques();
	for (Bloque* pBloque : bloques) {
		if (pBloque->isSolid() && _j1->isCollision(*pBloque)) {
			Personaje::Direcciones direccion = _j1->getDireccion();
			switch (direccion)
			{
			case Personaje::Direcciones::Down:
				_j1->move(0, -(_j1->getBounds().top + _j1->getBounds().height - pBloque->getBounds().top));
				break;
			case Personaje::Direcciones::Left:
				_j1->move((pBloque->getBounds().left + pBloque->getBounds().width - _j1->getBounds().left), 0);
				break;
			case Personaje::Direcciones::Right:
				_j1->move(-(_j1->getBounds().left + _j1->getBounds().width - pBloque->getBounds().left), 0);
				break;
			case Personaje::Direcciones::Up:
				_j1->move(0, (pBloque->getBounds().top + pBloque->getBounds().height - _j1->getBounds().top));
				break;
			}
		}
	}
}

void Juego::colisionesProyectil()
{
	/// iterator para recorrer todo la lista de proyectiles y actualizarlos.
	std::list<Proyectil*>::iterator i = _proyectiles.begin();
	while (i != _proyectiles.end()) {	
		Proyectil& p = (**i);
		p.update();
		if (colisionConBloques(p)) {
			delete (*i);
			i = _proyectiles.erase(i);
		}
		else {
			i++;
		}
	}
}

void Juego::colisionesEnemigo()
{
	/// iterator para recorrer todo la lista de enemigos y actualizarlos.
	std::list<Enemigo*>::iterator i = _enemigos.begin();
	while (i != _enemigos.end()) {
		Enemigo& e = (**i);
		e.update();
		if (_j1->isCollision(e)) {
			i = _enemigos.erase(i);
			_j1->setLastimado(true);
		}
		else if (colisionProyectilEnemigo(e)) {
			delete (*i);
			i = _enemigos.erase(i);
		}
		else {
			colisionConBloques(e);
			i++;
		}
	}
}

bool Juego::colisionConBloques(Proyectil& p)
{
	const std::vector<Bloque*>& bloques = _mapa->getBloques();
	for (Bloque* pBloque : bloques) {
		if (pBloque->isSolid() && p.isCollision(*pBloque)) {
			return true;
		}
	}
	return false;
}

void Juego::colisionConBloques(Enemigo& e)
{
	const std::vector<Bloque*>& bloques = _mapa->getBloques();
	for (Bloque* pBloque : bloques) {
		if (pBloque->isSolid() && e.isCollision(*pBloque)) {
			Enemigo::Direcciones oldDireccion = e.getDireccion();
			switch (oldDireccion)
			{
			case Enemigo::Direcciones::Up:
				e.move(0, (pBloque->getBounds().top + pBloque->getBounds().height - e.getBounds().top));
				break;
			case Enemigo::Direcciones::Left:
				e.move((pBloque->getBounds().left + pBloque->getBounds().width - e.getBounds().left), 0);
				break;
			case Enemigo::Direcciones::Down:
				e.move(0, -(e.getBounds().top + e.getBounds().height - pBloque->getBounds().top));
				break;
			case Enemigo::Direcciones::Right:
				e.move(-(e.getBounds().left + e.getBounds().width - pBloque->getBounds().left), 0);
				break;
			}
			Enemigo::Direcciones newDireccion = (Enemigo::Direcciones)(rand() % 4);
			while (newDireccion == oldDireccion) {
				newDireccion = (Enemigo::Direcciones)(rand() % 4);
			}
			e.setSentidoY(newDireccion);
			e.setSentidoX(0);
		}
	}
}


bool Juego::colisionProyectilEnemigo(Enemigo& e)
{
	std::list<Proyectil*>::iterator i = _proyectiles.begin();
	while (i != _proyectiles.end()) {
		Proyectil& p = (**i);
		if (p.isCollision(e)) {
			delete (*i);
			i = _proyectiles.erase(i);
			return true;
		}
		else {
			i++;
		}
	}
	return false;
}
	

void Juego::updateMusic() 
{  /// Actualizo controles de música
	if (_controller.isPressed(Controller::Buttons::ButtonLess) && _music.getVolume() > 1.f) {
		_music.setVolume(_music.getVolume() - 1.f);
	}
	else if (_controller.isPressed(Controller::Buttons::ButtonMore) && _music.getVolume() < 50.f) {
		_music.setVolume(_music.getVolume() + 1.f);
	}
	else if (_controller.isPressed(Controller::Buttons::ButtonMute)) {
		if (_music.getStatus() == _music.Playing) {
			_music.pause();
		}
		else _music.play();
	}
}


