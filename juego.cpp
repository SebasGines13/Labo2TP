#include <iostream>
#include "Juego.h"

Juego::Juego(sf::Vector2u resolucion)
{ //Constructor
	_ventana = new sf::RenderWindow(sf::VideoMode(resolucion.x, resolucion.y), "Dungeon ++ v0.9");
	_fps = 60;
	_dificultad = 1; /// Dificultad: 1 - fácil, 2 - Medio y 3 - Dificil
	_ventana->setFramerateLimit(_fps);
	_mapa = new Mapa(1, 16, 16, 50, 40); //Inicializo la variable dinámica para el mapa.
	_j1 = new Jugador(1, *this, _controller); ///Inicilizo la variable dinámica de jugador.
	_j1->setPosition(sf::Vector2f(_mapa->getPlayerSpawn())); /// Ubico el personaje de acuerdo a spawn definido en el mapa.
	_gui = new GUI(_dificultad);
	_listado = new Listado();
	_configuracion = new Configuracion();
	_menu = new Menu();
	_music.openFromFile("audio/fondo.wav");
	_music.play();
	_music.setVolume(10.f);
	_gameOver = false;
	_bienvenidaAjuego = true;
	srand(time(NULL));
	int i = rand() % 3; /// para obtener el lugar de respawn de enemigos
	int j = rand() % 10; /// para manejar el aleatorio de tipo de enemigos (mayor velocidad de desplazamiento)
	if (j > 6) {
		_enemigos.push_back(new Enemigo(11, 5.f, sf::Vector2f(_mapa->getEnemigoSpawn(i))));
	}
	else {
		_enemigos.push_back(new Enemigo(11, 3.f, sf::Vector2f(_mapa->getEnemigoSpawn(i))));
	}
	switch (_dificultad) ///  de acuerdo a la velocidad, asigno más o menos frecuencia de respawn de enemigos.
	{
	case 1:
		coolDownEnemigos = 80;
		break;
	case 2:
		coolDownEnemigos = 50;
		break;
	case 3:
		coolDownEnemigos = 30;
		break;
	}
	_coolDown[(int)coolDown::Lastimado] = COOLDOWNLASTIMADO;
	_coolDown[(int)coolDown::Enemigo] = coolDownEnemigos;
	_coolDown[(int)coolDown::ItemPantalla ] = COOLDOWNITEMPANTALLA;
	_coolDown[(int)coolDown::Menu] = COOLDOWNMENU;
	gameLoop();
}

Juego::~Juego()
{
	delete _ventana;
	delete _j1;
	delete _mapa;
	delete _menu;
	delete _gui;
	delete _listado;
	delete _configuracion;
}

void Juego::reiniciarJuego() 
{
	/// Eliminamos los objetos (si es que están creados) para iniciar un nuevo juego.
	if(_j1)  delete _j1;
	if(_mapa)delete _mapa;
	if(_gui) delete _gui;
	_enemigos.clear();
	/// Creamos los objetos para iniciar un nuevo juego.
	_mapa  = new Mapa(1, 16, 16, 50, 40); //Inicializo la variable dinámica para el mapa.
	_j1	   = new Jugador(1, *this, _controller); ///Inicilizo la variable dinámica de jugador.
	_gui   = new GUI(_dificultad); /// Inicializo la variable para mostrar la vida y el puntaje.
	_j1->setPosition(sf::Vector2f(_mapa->getPlayerSpawn())); /// Ubico el personaje de acuerdo a spawn definido en el mapa.
	switch (_dificultad) ///  de acuerdo a la velocidad, asigno más o menos frecuencia de respawn de enemigos.
	{
	case 1:
		coolDownEnemigos = 80;
		break;
	case 2:
		coolDownEnemigos = 50;
		break;
	case 3:
		coolDownEnemigos = 30;
		break;
	}
	_coolDown[(int)coolDown::Enemigo] = coolDownEnemigos;
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
		if (_menu->getOpcMenuPress()[(int)Menu::OpcMenu::Play] ) {
			if (_bienvenidaAjuego) { // primera pantalla antes de jugar
				do {
					_bienvenidaAjuego = false;
					_ventana->clear();
					_menu->getSprFuego()->animar();
					_ventana->draw(_menu->getSprFondo());
					_ventana->draw(_menu->getSprControles());					
					_ventana->draw(*_menu->getSprFuego());
					_ventana->display();
				} while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
				_menu->getSonidoTeclas().play();
				for (int i = 1; i < COOLDOWNMENU; i++) { // acercamiento a la entrada del dungeon.
					_ventana->clear();
					_menu->getSprCamino().setScale(sf::Vector2f(1+(i/60.f), 1+(i/60.f)));
					_ventana->draw(_menu->getSprCamino());
					_ventana->display();
				}
				reiniciarJuego(); /// para reiniciar los objetos necesarios en caso de que haya modificado la dificultad
			}
			else {// ya entra al juego
				command();
				update();
				draw();
			}			
		}
		else if (_menu->getOpcMenuPress()[(int)Menu::OpcMenu::Exit]) {
			_gameOver = true;
		}
		else if (_menu->getOpcMenuPress()[(int)Menu::OpcMenu::Ranking]) {
			ranking();
		}
		else if (_menu->getOpcMenuPress()[(int)Menu::OpcMenu::Config]) {
			configuracion();
			reiniciarJuego();
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
	_mapa->update();
	colisionesJugadorBloques();
	colisionesProyectilBloques();
	colisionesEnemigoBloques();
	colisionesJugadorItem();
	if (_gui->getVidasRestantes() <= 0) { ///  
		grabarPuntaje();
		reiniciarJuego();
		_menu->getOpcMenuPress()[(int)Menu::OpcMenu::Play] = false; /// Para que regrese al menu principal
		_bienvenidaAjuego = true; // Para que muestre la entrada a las mazmorras y los controles.	
	}
	else {
		coolDowns();
		updateMusic(); /// actualiza música por si se presionó para mute, subir o a bajar el volumen.
	}
}

void Juego::coolDowns() {
	_coolDown[(int)coolDown::Lastimado] --; /// para evaluar si está lastimado el personaje
	if (_coolDown[(int)coolDown::Lastimado] == 0) {
		_coolDown[(int)coolDown::Lastimado] = COOLDOWNLASTIMADO;
		_j1->setLastimado(false);
	}

	_coolDown[(int)coolDown::Enemigo] --; /// para evaluar el respawn de enemigos
	if (_coolDown[(int)coolDown::Enemigo] == 0) {
		int i = rand() % 3;
		int j = rand() % 10;
		if (j > 6) {
			_enemigos.push_back(new Enemigo(11, 5.f, sf::Vector2f(_mapa->getEnemigoSpawn(i))));
		}
		else {
			_enemigos.push_back(new Enemigo(11, 3.f, sf::Vector2f(_mapa->getEnemigoSpawn(i))));
		}
		_coolDown[(int)coolDown::Enemigo] = coolDownEnemigos;
	}
	if (_mapa->getItemVisible()) { // si existe un item visible en el mapa, evaluamos si tiene que desaparecer
		_coolDown[(int)coolDown::ItemPantalla] --; // para evaluar si existe un item para desaparecerlo de la pantalla
		if (_coolDown[(int)coolDown::ItemPantalla] == 0) {
			_mapa->desaparecerItem(); // desaparece el item
			_coolDown[(int)coolDown::ItemPantalla] = COOLDOWNITEMPANTALLA;
		}
	}
}

void Juego::grabarPuntaje() {
	sf::Clock clock; /// reloj para el parpadeo del cursor en el ingreso del nombre.
	bool salir = false;
	std::string input_text;
	sf::Font fuente;
	fuente.loadFromFile("font/CELTG.ttf");
	sf::Text vText[5];

	for (int i = 0; i < std::size(vText); i++) {
		vText[i].setFont(fuente);
		vText[i].setCharacterSize(40);
		vText[i].setFillColor(sf::Color(255, 255, 255, 180));
		switch (i)
		{
		case 0:
			vText[i].setString("Juego terminado...");
			vText[i].setPosition(8.f, 150.f);
			vText[i].setCharacterSize(78);
			vText[i].setFillColor(sf::Color(255, 255, 255, 220));
			break;
		case 1:
			vText[i].setString("Tu puntaje total es: '" + std::to_string(_gui->getPuntaje())+ "'");
			vText[i].setPosition(10, 200.f + (i * 110));
			break;
		case 2:
			vText[i].setString("Nombre (6 caract. max):");
			vText[i].setPosition(10, 200.f + (i * 110));
			break;
		case 3:
			vText[i].setString(" "); /// lo seteo más adelante con el ingreso del texto por parte del usuario.
			vText[i].setPosition(570.f, 200.f + ((i-1) * 110));
			break;
		case 4:
			vText[i].setString("Presione la tecla 'ENTER' para continuar...");
			vText[i].setPosition(50.f, 600.f);
			vText[i].setCharacterSize(30);
			break;
		}
	}

	while (_ventana->isOpen() && (!salir))
	{
		sf::Event event;
		while (_ventana->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_ventana->close();
			else if (event.type == sf::Event::TextEntered && input_text.length()<=5) {
				if (std::isprint(event.text.unicode))
					input_text += event.text.unicode;
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::BackSpace) {
					if (!input_text.empty())
						input_text.pop_back();
				}
				if (event.key.code == sf::Keyboard::Return) {
					input_text += '\n';
				}
				if (event.key.code == sf::Keyboard::Enter) {
					Ranking reg;
					reg.setJugador(input_text);
					reg.setPuntaje(_gui->getPuntaje());
					reg.GuardarEnDisco();
					salir = true;
				}
			}
		}
		static sf::Time text_effect_time;
		static bool show_cursor = false;
		text_effect_time += clock.restart();
		if (text_effect_time >= sf::seconds(0.5f))
		{
			show_cursor = !show_cursor;
			text_effect_time = sf::Time::Zero;
		}
		vText[3].setString(input_text + (show_cursor ? '_' : ' '));		
		_ventana->clear();
		_menu->getSprFuego()->animar();
		_ventana->draw(_menu->getSprFondo());
		_ventana->draw(*_menu->getSprFuego());
		for (int i = 0; i < std::size(vText);i++) {
			_ventana->draw(vText[i]);
		}
		_ventana->display();
	}
}

void Juego::ranking()
{
	bool salir = false;
	_listado->listarRanking(); // Preparo el listado de rankings de puntaje
	while (_ventana->isOpen() && (!salir))
	{
		sf::Event event;
		while (_ventana->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_ventana->close();
			else if (event.key.code == sf::Keyboard::Space) {
				salir = true;
			}
		}
		_ventana->clear();
		_menu->getSprFuego()->animar();
		_ventana->draw(_menu->getSprFondo());
		_ventana->draw(*_menu->getSprFuego());
		_ventana->draw(*_listado);
		_ventana->display();
	}
	_menu->getOpcMenuPress()[(int)Menu::OpcMenu::Ranking] = false; /// Para que regrese al menu principal
}

void Juego::configuracion() 
{
	bool salir = false;	
	bool bMusica = false;
	if (_music.getStatus() == _music.Playing) bMusica = true;
	else bMusica = false;
	while (_ventana->isOpen() && (!salir))
	{
		sf::Event event;
		while (_ventana->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_ventana->close();
			else if (event.key.code == sf::Keyboard::Space) {
				salir = true;
			}
		}
		_configuracion->menu(bMusica, _dificultad); // Configuraciones
		_ventana->clear();
		_menu->getSprFuego()->animar();
		_ventana->draw(_menu->getSprFondo());
		_ventana->draw(*_menu->getSprFuego());
		_ventana->draw(*_configuracion);
		_ventana->display();
	}
	if (!bMusica) _music.stop();
	else if(!(_music.getStatus() == _music.Playing)) _music.play();
	_menu->getOpcMenuPress()[(int)Menu::OpcMenu::Config] = false; /// Para que regrese al menu principal
}




void Juego::draw()
{	///Dibuja en pantalla los elementos.
	_ventana->clear(); ///Limpio la pantalla con lo que había antes.
	_ventana->draw(*_mapa); /// Dibujo el mapa
	_ventana->draw(*_gui); /// Dibujo la interfaz de GUI para por ejemplo la vida y el puntaje
	_ventana->draw(*_j1); /// Dibujo el personaje.	
	for (Enemigo *e : _enemigos) { /// recorro con un for each la lista de enemigos y los dibujo
		_ventana->draw(*e);
	}
	for (Proyectil *p : _proyectiles) { /// recorro con un for each la lista de proyectiles y las dibujo
		_ventana->draw(*p);
	}
	_ventana->display();//Muestro la ventana.
}

void Juego::crearProyectil(sf::Vector2f posicion, Proyectil::Direcciones direccion)
{
	_proyectiles.push_back(new Proyectil(posicion, direccion));
}

void Juego::colisionesJugadorBloques() /// el juego evalua cuando el jugador colisiona con los bloques y qué hacer con él en caso de que sea sólido.
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

void Juego::colisionesJugadorItem()
{
	Item item = _mapa->getItem();
	if (_mapa->getItemVisible() && _j1->isCollision(item))
	{
		_gui->sumarPuntos(10, _dificultad);
		_mapa->desaparecerItem();
		_coolDown[(int)coolDown::ItemPantalla] = COOLDOWNITEMPANTALLA;
	}
}


void Juego::colisionesProyectilBloques()
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

void Juego::colisionesEnemigoBloques()
{
	/// iterator para recorrer todo la lista de enemigos y actualizarlos.
	std::list<Enemigo*>::iterator i = _enemigos.begin();
	while (i != _enemigos.end()) {
		Enemigo& e = (**i);
		e.update();
		if (_j1->isCollision(e)) {
			i = _enemigos.erase(i);
			_j1->setLastimado(true);
			_gui->restarVida(1);
		}
		else if (colisionProyectilEnemigo(e)) {
			if (e.getVelDesplaz() > 3.f) _gui->sumarPuntos(2, _dificultad);
			else _gui->sumarPuntos(1, _dificultad);
			/// si el jugador impactó con un proyectil, evaluamos la posibilidad de que se genere una recompensa en forma de item.
			if (!(_mapa->getItemVisible())) { /// si no existe ya un item en pantalla, comienzo a evaluar random.
				int i = rand() % 10;
				if (i > 6) {
					_mapa->spawnItem(e.getPosition());
				}
			}
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
			e.setDireccion(newDireccion);
			e.setSpriteQuieto();
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
