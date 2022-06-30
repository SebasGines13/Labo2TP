#include <iostream>
#include "Juego.h"

Juego::Juego(sf::Vector2u resolucion)
{ //Constructor
	_ventana = new sf::RenderWindow(sf::VideoMode(resolucion.x, resolucion.y), "Dungeon ++ v1.1");
	_fps = 60;
	_dificultad = 1; /// Dificultad: 1 - f�cil, 2 - Medio y 3 - Dificil
	_ventana->setFramerateLimit(_fps);
	_listado = new Listado();
	_configuracion = new Configuracion();
	_menu = new Menu();
	_music.openFromFile("audio/fondo.wav");
	_music.play();
	_music.setVolume(10.f);
	_music.setLoop(true);
	_gameOver = false;
	_bienvenidaAjuego = true;
	_nivelMapa = 1;
	srand(time(NULL));
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

void Juego::PrepararJuego(int modo) 
{
	if (_mapa) delete _mapa;
	_mapa = new Mapa(1, modo, 16, 16, 50, 40); //Inicializo la variable din�mica para el mapa.
	if (modo == 1) {
		/// Eliminamos o limpiamos los objetos (si es que est�n creados) para iniciar un nuevo juego.
		if (_j1)   delete _j1;
		if (_gui)  delete _gui;
		/// Creamos los objetos para iniciar un nuevo juego.
		_j1 = new Jugador(1, *this, _controller, _dificultad, COOLDOWNJUGADORLASTIMADO); ///Inicilizo la variable din�mica de jugador.
		_gui = new GUI(_j1->getVida(), TIEMPOJEFE); /// Inicializo la variable para mostrar la vida y el puntaje.		
		switch (_dificultad) ///  de acuerdo a la dificultad, asigno m�s o menos frecuencia de respawn de enemigos.
		{
		case 1:
			_coolDownEnemigos = 120;
			break;
		case 2:
			_coolDownEnemigos = 80;
			break;
		case 3:
			_coolDownEnemigos = 30;
			break;
		}
		_nroJefeActual = 0;
		_nivelMapa = 1;
	}
	else {
		_gui->reiniciarTiempo();
	}
	_j1->setPosition(sf::Vector2f(_mapa->getPlayerSpawn())); /// Ubico el personaje de acuerdo a spawn definido en el mapa.
	_enemigos.clear();
	_proyectiles.clear();
	crearEnemigo();
	_juegoGanado = false;
	_pasoNivel = false;
	_coolDown[(int)coolDown::Enemigo] = _coolDownEnemigos;
	_coolDown[(int)coolDown::ItemPantalla] = COOLDOWNITEMPANTALLA;
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
				PrepararJuego(1);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) { /// Para quitar la m�sica
		_controller.push(Controller::Buttons::ButtonMute);
	}	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) { /// Para bajar m�sica
		_controller.push(Controller::Buttons::ButtonLess);		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) { /// Para subir m�sica
		_controller.push(Controller::Buttons::ButtonMore);
	}
}

void Juego::update()
{   ///L�gicas y reglas propias del juego.
	_j1->update();
	_mapa->update();
	colisionesJugadorBloques();
	colisionesJugadorItem();
	colisionesProyectilBloques();
	colisionesEnemigo();

	if (_juegoGanado) {
		ganarJuego();
	}
	else if (_pasoNivel) {
		avanzarNivel();
		PrepararJuego(2); /// 1 se reinicia el juego, con el 2 avanzo al siguiente mapa. Se limpian los objetos dependiendo de cada caso.
	}
	else if (_gui->getVidasRestantes() <= 0) {
		grabarPuntaje();
	}
	else {
		coolDowns();
		updateMusic(); /// actualiza m�sica por si se presion� para mute, subir o a bajar el volumen.
		_gui->update();
		spawnJefe();
	}
}

void Juego::spawnJefe() 
{
	if (_gui->esTiempoJefe()) {
		if (_nroJefeActual > 1 && _nivelMapa == 1) {
			_nivelMapa++;
			_pasoNivel = true;
		}
		else if (_nroJefeActual < 4) {
				int i = rand() % 3;
				_enemigos.push_back(new Enemigo(3 + _nroJefeActual, sf::Vector2f(_mapa->getEnemigoSpawn(i)), _dificultad, COOLDOWNENEMIGOLASTIMADO)); /// genero el jefe.			
				_gui->setStopTiempo(true);
				_nroJefeActual++;
		}
		else _juegoGanado = true;	
	}
}

void Juego::coolDowns() {
	if (_j1->getLastimado()) {
		_j1->setCoolDownLastimado(-1); /// para evaluar si est� lastimado el personaje
		if (_j1->getCoolDownLastimado() == 0) {
			_j1->setCoolDownLastimado(COOLDOWNJUGADORLASTIMADO);
			_j1->setLastimado(false);
		}
	}
	_coolDown[(int)coolDown::Enemigo] --; /// para evaluar el respawn de enemigos
	if (_coolDown[(int)coolDown::Enemigo] == 0) {
		crearEnemigo();
		_coolDown[(int)coolDown::Enemigo] = _coolDownEnemigos;
	}

	if (_mapa->getItemVisible(1)) { // si existe un item de tipo puntos visible en el mapa, evaluamos si tiene que desaparecer
		_coolDown[(int)coolDown::ItemPantalla] --; // para evaluar si existe un item para desaparecerlo de la pantalla
		if (_coolDown[(int)coolDown::ItemPantalla] == 0) {
			_mapa->desaparecerItem(1); // desaparece el item
			_coolDown[(int)coolDown::ItemPantalla] = COOLDOWNITEMPANTALLA;
		}
	} else if (_mapa->getItemVisible(2)) { // si existe un item de tipo vida visible en el mapa, evaluamos si tiene que desaparecer
		_coolDown[(int)coolDown::ItemPantalla] --; // para evaluar si existe un item para desaparecerlo de la pantalla
		if (_coolDown[(int)coolDown::ItemPantalla] == 0) {
			_mapa->desaparecerItem(2); // desaparece el item
			_coolDown[(int)coolDown::ItemPantalla] = COOLDOWNITEMPANTALLA;
		}
	}

	std::list<Enemigo*>::iterator i = _enemigos.begin();
	while (i != _enemigos.end()) {
		Enemigo& e = (**i);
		if (e.getLastimado()) { //para evaluar si est� lastimado el enemigo, le bajo el cooldown de lastimado
			e.setCoolDownLastimado(-1);
			if (e.getCoolDownLastimado() == 0) {
				e.setCoolDownLastimado(COOLDOWNENEMIGOLASTIMADO);
				e.setLastimado(false);
			}
		}
		i++; /// para continuar evaluando el resto de proyectiles.
	}
}

void Juego::crearEnemigo() {
	int i = rand() % 3;
	int j = rand() % 10;
	if (j > 6) {
		_enemigos.push_back(new Enemigo(2, sf::Vector2f(_mapa->getEnemigoSpawn(i)), _dificultad, COOLDOWNENEMIGOLASTIMADO));
	}
	else {
		_enemigos.push_back(new Enemigo(1, sf::Vector2f(_mapa->getEnemigoSpawn(i)), _dificultad, COOLDOWNENEMIGOLASTIMADO));
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
			vText[i].setString(" "); /// lo seteo m�s adelante con el ingreso del texto por parte del usuario.
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
					_menu->getSonidoTeclas().play();
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
					Ranking *reg = NULL;
					reg = new Ranking;
					reg->setJugador(input_text);
					reg->setPuntaje(_gui->getPuntaje());
					reg->GuardarEnDisco();
					salir = true;
					delete reg;
					
				}
				_menu->getSonidoTeclas().play();
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
	_menu->getOpcMenuPress()[(int)Menu::OpcMenu::Play] = false; /// Para que regrese al menu principal
	_bienvenidaAjuego = true; // Para que muestre la entrada a las mazmorras y los controles.	
}

void Juego::avanzarNivel() {
	bool continuar = false;
	sf::Font fuente;
	fuente.loadFromFile("font/CELTG.ttf");
	sf::Text vText[4];

	for (int i = 0; i < std::size(vText); i++) {
		vText[i].setFont(fuente);
		vText[i].setCharacterSize(30);
		vText[i].setFillColor(sf::Color(255, 255, 255, 180));
		switch (i)
		{
		case 0:
			vText[i].setString("Nivel superado...");
			vText[i].setPosition(8.f, 150.f);
			vText[i].setCharacterSize(78);
			vText[i].setFillColor(sf::Color(255, 255, 255, 220));
			break;
		case 1:
			vText[i].setString("Listo para el siguiente reto?");
			vText[i].setPosition(10, 200.f + (i * 110));
			break;
		case 2:
			vText[i].setString("Tu puntaje hasta el momento es: '" + std::to_string(_gui->getPuntaje()) + "'");
			vText[i].setPosition(10, 200.f + (i * 110));
			break;
		case 3:
			vText[i].setString("Presione la tecla 'ENTER' para continuar...");
			vText[i].setPosition(50.f, 600.f);
			break;
		}
	}

	while (_ventana->isOpen() && (!continuar))
	{
		sf::Event event;
		while (_ventana->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_ventana->close();
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Enter) {
					continuar = true;
					_menu->getSonidoTeclas().play();
				}				
			}
		}
		_ventana->clear();
		_menu->getSprFuego()->animar();
		_ventana->draw(_menu->getSprFondo());
		_ventana->draw(*_menu->getSprFuego());
		for (int i = 0; i < std::size(vText);i++) {
			_ventana->draw(vText[i]);
		}
		_ventana->display();
	}

	if (continuar) {
		delete _mapa;
		_mapa = new Mapa(1, _nivelMapa, 16, 16, 50, 40);
	}
}

void Juego::ganarJuego() {
	sf::Clock clock; /// reloj para el parpadeo del cursor en el ingreso del nombre.
	bool salir = false;
	std::string input_text;
	sf::Font fuente;
	fuente.loadFromFile("font/CELTG.ttf");
	sf::Text vText[6];
	int puntajeFinal = _gui->getPuntaje() * 10;

	for (int i = 0; i < std::size(vText); i++) {
		vText[i].setFont(fuente);
		vText[i].setCharacterSize(30);
		vText[i].setFillColor(sf::Color(255, 255, 255, 180));
		switch (i)
		{
		case 0:
			vText[i].setString("FELICIDADES!!");
			vText[i].setPosition(8.f, 150.f);
			vText[i].setCharacterSize(70);
			vText[i].setFillColor(sf::Color(255, 255, 255, 220));
			break;
		case 1:
			vText[i].setString("Has derrotado a los Magos Supremos...");
			vText[i].setPosition(10, 200.f + (i * 110));
			break;
		case 2:
			vText[i].setString("Tu puntaje total es: '" + std::to_string(puntajeFinal) + "'");
			vText[i].setPosition(10, 200.f + (i * 110));
			break;
		case 3:
			vText[i].setString("Nombre (6 caract. max):");
			vText[i].setPosition(10, 200.f + (i * 110));
			break;
		case 4:
			vText[i].setString(" "); /// lo seteo m�s adelante con el ingreso del texto por parte del usuario.
			vText[i].setPosition(570.f, 200.f + ((i - 1) * 110));
			break;
		case 5:
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
			else if (event.type == sf::Event::TextEntered && input_text.length() <= 5) {
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
					Ranking* reg = NULL;
					reg = new Ranking;
					reg->setJugador(input_text);
					reg->setPuntaje(puntajeFinal);
					reg->GuardarEnDisco();
					salir = true;
					delete reg;
				}
				_menu->getSonidoTeclas().play();
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
		vText[4].setString(input_text + (show_cursor ? '_' : ' '));
		_ventana->clear();
		_menu->getSprFuego()->animar();
		_ventana->draw(_menu->getSprFondo());
		_ventana->draw(*_menu->getSprFuego());
		for (int i = 0; i < std::size(vText);i++) {
			_ventana->draw(vText[i]);
		}
		_ventana->display();
	}
	_menu->getOpcMenuPress()[(int)Menu::OpcMenu::Play] = false; /// Para que regrese al menu principal
	_bienvenidaAjuego = true; // Para que muestre la entrada a las mazmorras y los controles.	
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
				_menu->getSonidoTeclas().play();
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
				_menu->getSonidoTeclas().play();
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
	_ventana->clear(); ///Limpio la pantalla con lo que hab�a antes.
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

void Juego::crearProyectil(sf::Vector2f posicion)
{
	_proyectiles.push_back(new Proyectil(posicion));
}

void Juego::colisionesJugadorBloques() /// el juego evalua cuando el jugador colisiona con los bloques y qu� hacer con �l en caso de que sea s�lido.
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
	Item itemPuntos = _mapa->getItem(1);
	Item itemVida = _mapa->getItem(2);
	if (_mapa->getItemVisible(1) && _j1->isCollision(itemPuntos))
	{
		_gui->sumarPuntos(10, _dificultad);
		_mapa->desaparecerItem(1);
		_coolDown[(int)coolDown::ItemPantalla] = COOLDOWNITEMPANTALLA;
	} 
	else if (_mapa->getItemVisible(2) && _j1->isCollision(itemVida))
	{
		_gui->sumarVida(1);
		_j1->sumarVida(1);
		_mapa->desaparecerItem(2);
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

void Juego::colisionesEnemigo()
{
	/// iterator para recorrer todo la lista de enemigos y actualizarlos.
	std::list<Enemigo*>::iterator i = _enemigos.begin();
	while (i != _enemigos.end()) {
		Enemigo& e = (**i);
		int tipoEnemigo = e.getTipoEnemigo();
		int golpe = (tipoEnemigo > 2 ? 2 : 1);
		e.update();
		if (_j1->isCollision(e)) {
			if (!e.getLastimado()) {
				e.recibirGolpe(1);
			}			
			if (e.getVida() <= 0) {
				delete (*i);
				i = _enemigos.erase(i);
				if(tipoEnemigo>2) _gui->setStopTiempo(false); // si se elimin� a un jefe, permito que reinicie el conteo para el siguiente jefe
			} else i++;
			if (!_j1->getLastimado()) {
				_j1->recibirGolpe(golpe);
				_gui->restarVida(golpe);
			}
		}
		else if (colisionProyectilEnemigo(e)) {
			if (!e.getLastimado()) {
				e.recibirGolpe(1);
				if (e.getVida() <= 0) {
					_gui->sumarPuntos(tipoEnemigo, _dificultad);
					/// si el jugador impact� con un proyectil a un enemigo y lo elimin�, evaluamos la posibilidad de que se genere una recompensa en forma de item.
					if (!(_mapa->getItemVisible(1)) && !(_mapa->getItemVisible(2))) { /// si no existe ya un item en pantalla, comienzo a evaluar random.
						int i = (rand() % 10) + (tipoEnemigo * 5);
						if (i >= 15) {
							_mapa->spawnItem(e.getPosition(), 2);
						}
						else if (i >= 12) {
							_mapa->spawnItem(e.getPosition(), 1);
						}
					}
					delete (*i);
					i = _enemigos.erase(i);
					if (tipoEnemigo > 2) _gui->setStopTiempo(false); // si se elimin� a un jefe, permito que reinicie el conteo para el siguiente jefe
				} 
			}
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
			i++; /// para continuar evaluando el resto de proyectiles.
		}
	}
	return false;
}
	

void Juego::updateMusic() 
{  /// Actualizo controles de m�sica
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
