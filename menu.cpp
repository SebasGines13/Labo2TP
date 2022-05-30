#include "Menu.h"


Menu::Menu()
{
	_font.loadFromFile("font/CELTG.ttf");
	_gameTitle.setFont(_font);
	_gameTitle.setString("Dungeon++");
	_gameTitle.setCharacterSize(100); 
	_gameTitle.setFillColor(sf::Color(255, 255, 255, 128));
	_gameTitle.setOrigin(_gameTitle.getGlobalBounds().width / 2, _gameTitle.getGlobalBounds().height / 2);
	_gameTitle.setPosition(400.f, 250.f);
	_txtFondo.loadFromFile("img/dungeon_menu.png");
	_txtControles.loadFromFile("img/controles.png");
	_txtCaminoDun.loadFromFile("img/camino_mazmorra.png");
	_txtFondo.setSmooth(true);
	_txtControles.setSmooth(true);
	_txtCaminoDun.setSmooth(true);
	_sprFondo.setTexture(_txtFondo);
	_sprControles.setTexture(_txtControles);
	_sprFondo.setColor(sf::Color(255, 255, 255, 150));
	_sprCaminoDun.setColor(sf::Color(255, 255, 255, 150));
	_sprFuego = new Sprite(17, 75, 1, sf::Vector2f(0,0), 2.f);
	_sprFuego->setPosicion(sf::Vector2f(550.f,5.f));
	_sprCaminoDun.setTexture(_txtCaminoDun);
	_sprCaminoDun.setOrigin(sf::Vector2f(_txtCaminoDun.getSize().x  /2, _txtCaminoDun.getSize().y / 2));
	_buffer.loadFromFile("audio/teclas_menu.wav");
	_soundTeclas.setBuffer(_buffer);
	_soundTeclas.setVolume(40.f);

	for (int i = 0; i < std::size(_vButtons); i++) { /// creo las opciones del menú
		switch (i)
		{
		case (int)OpcMenu::Play:
			_vButtons[i].setFont(_font);
			_vButtons[i].setString("Play");
			_vButtons[i].setCharacterSize(20);
			_vButtons[i].setFillColor(sf::Color(255, 255, 255, 128));
			_vButtons[i].setOrigin(_vButtons[i].getGlobalBounds().width / 2, _vButtons[i].getGlobalBounds().height / 2);
			_vButtons[i].setPosition(400.f, 400.f +(40 * i));
			break;
		case (int)OpcMenu::Ranking:
			_vButtons[i].setFont(_font);
			_vButtons[i].setString("Ranking");
			_vButtons[i].setCharacterSize(20);
			_vButtons[i].setFillColor(sf::Color(255, 255, 255, 128));
			_vButtons[i].setOrigin(_vButtons[i].getGlobalBounds().width / 2, _vButtons[i].getGlobalBounds().height / 2);
			_vButtons[i].setPosition(400.f, 400.f + (40 * i));
			break;
		default:
		case (int)OpcMenu::Config:
			_vButtons[i].setFont(_font);
			_vButtons[i].setString("Config");
			_vButtons[i].setCharacterSize(20);
			_vButtons[i].setFillColor(sf::Color(255, 255, 255, 128));
			_vButtons[i].setOrigin(_vButtons[i].getGlobalBounds().width / 2, _vButtons[i].getGlobalBounds().height / 2);
			_vButtons[i].setPosition(400.f, 400.f + (40 * i));
			break;
		case (int)OpcMenu::Credit:
			_vButtons[i].setFont(_font);
			_vButtons[i].setString("Credit");
			_vButtons[i].setCharacterSize(20);
			_vButtons[i].setFillColor(sf::Color(255, 255, 255, 128));
			_vButtons[i].setOrigin(_vButtons[i].getGlobalBounds().width / 2, _vButtons[i].getGlobalBounds().height / 2);
			_vButtons[i].setPosition(400.f, 400.f + (40 * i));
			break;
		case (int)OpcMenu::Exit:
			_vButtons[i].setFont(_font);
			_vButtons[i].setString("Exit");
			_vButtons[i].setCharacterSize(20);
			_vButtons[i].setFillColor(sf::Color(255, 255, 255, 128));
			_vButtons[i].setOrigin(_vButtons[i].getGlobalBounds().width / 2, _vButtons[i].getGlobalBounds().height / 2);
			_vButtons[i].setPosition(400.f, 400.f + (40 * i));
			break;
		}
	}
}

void Menu::command() { /// Segun las teclas presionadas, se indica la selcción.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		_soundTeclas.play();
		if (_vOpcMenuSelect[(int)OpcMenu::Play]) {
			_vOpcMenuSelect[(int)OpcMenu::Play] = false;
			_vOpcMenuSelect[(int)OpcMenu::Exit] = true;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Ranking]) {
			_vOpcMenuSelect[(int)OpcMenu::Play] = true;
			_vOpcMenuSelect[(int)OpcMenu::Ranking] = false;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Config]) {
			_vOpcMenuSelect[(int)OpcMenu::Ranking] = true;
			_vOpcMenuSelect[(int)OpcMenu::Config] = false;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Credit]) {
			_vOpcMenuSelect[(int)OpcMenu::Config] = true;
			_vOpcMenuSelect[(int)OpcMenu::Credit] = false;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Exit]) {
			_vOpcMenuSelect[(int)OpcMenu::Credit] = true;
			_vOpcMenuSelect[(int)OpcMenu::Exit] = false;
		}
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
		_soundTeclas.play();
		if (_vOpcMenuSelect[(int)OpcMenu::Play]) {
			_vOpcMenuSelect[(int)OpcMenu::Play] = false;
			_vOpcMenuSelect[(int)OpcMenu::Ranking] = true;			
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Ranking]) {
			_vOpcMenuSelect[(int)OpcMenu::Ranking] = false;
			_vOpcMenuSelect[(int)OpcMenu::Config] = true;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Config]) {
			_vOpcMenuSelect[(int)OpcMenu::Config] = false;
			_vOpcMenuSelect[(int)OpcMenu::Credit] = true;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Credit]) {
			_vOpcMenuSelect[(int)OpcMenu::Credit] = false;
			_vOpcMenuSelect[(int)OpcMenu::Exit] = true;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Exit]) {
			_vOpcMenuSelect[(int)OpcMenu::Exit] = false;
			_vOpcMenuSelect[(int)OpcMenu::Play] = true;
		}
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))) {
		_soundTeclas.play();
		if (_vOpcMenuSelect[(int)OpcMenu::Play]) {
			_vOpcMenuPress[(int)OpcMenu::Play] = true;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Ranking]) {
			_vOpcMenuPress[(int)OpcMenu::Ranking] = true;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Config]) {
			_vOpcMenuPress[(int)OpcMenu::Config] = true;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Credit]) {
			_vOpcMenuPress[(int)OpcMenu::Credit] = true;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Exit]) {
			_vOpcMenuPress[(int)OpcMenu::Exit] = true;
		}
	}
}

void Menu::update()  /// Segun las teclas seleccionada, actualizo colores y tamaño de los botones
{
	if (_vOpcMenuSelect[(int)OpcMenu::Play]) {
		_vButtons[(int)OpcMenu::Play].setFillColor(sf::Color::Yellow);
		_vButtons[(int)OpcMenu::Ranking].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Config].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Credit].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Exit].setFillColor(sf::Color(255, 255, 255, 128));

		_vButtons[(int)OpcMenu::Play].setScale(sf::Vector2f(1.5f, 1.5f));
		_vButtons[(int)OpcMenu::Ranking].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Config].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Credit].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Exit].setScale(sf::Vector2f(1.f, 1.f));

	}
	else if (_vOpcMenuSelect[(int)OpcMenu::Ranking]) {
		_vButtons[(int)OpcMenu::Play].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Ranking].setFillColor(sf::Color::Yellow);
		_vButtons[(int)OpcMenu::Config].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Credit].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Exit].setFillColor(sf::Color(255, 255, 255, 128));

		_vButtons[(int)OpcMenu::Play].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Ranking].setScale(sf::Vector2f(1.5f, 1.5f));
		_vButtons[(int)OpcMenu::Config].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Credit].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Exit].setScale(sf::Vector2f(1.f, 1.f));
	}
	else if (_vOpcMenuSelect[(int)OpcMenu::Config]) {
		_vButtons[(int)OpcMenu::Play].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Ranking].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Config].setFillColor(sf::Color::Yellow);
		_vButtons[(int)OpcMenu::Credit].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Exit].setFillColor(sf::Color(255, 255, 255, 128));

		_vButtons[(int)OpcMenu::Play].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Ranking].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Config].setScale(sf::Vector2f(1.5f, 1.5f));
		_vButtons[(int)OpcMenu::Credit].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Exit].setScale(sf::Vector2f(1.f, 1.f));
	}
	else if (_vOpcMenuSelect[(int)OpcMenu::Credit]) {
		_vButtons[(int)OpcMenu::Play].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Ranking].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Config].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Credit].setFillColor(sf::Color::Yellow);
		_vButtons[(int)OpcMenu::Exit].setFillColor(sf::Color(255, 255, 255, 128));

		_vButtons[(int)OpcMenu::Play].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Ranking].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Config].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Credit].setScale(sf::Vector2f(1.5f, 1.5f));
		_vButtons[(int)OpcMenu::Exit].setScale(sf::Vector2f(1.f, 1.f));
	}
	else if (_vOpcMenuSelect[(int)OpcMenu::Exit]) {
		_vButtons[(int)OpcMenu::Play].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Ranking].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Config].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Credit].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::Exit].setFillColor(sf::Color::Yellow);

		_vButtons[(int)OpcMenu::Play].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Ranking].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Config].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Credit].setScale(sf::Vector2f(1.f, 1.f));
		_vButtons[(int)OpcMenu::Exit].setScale(sf::Vector2f(1.5f, 1.5f));
	}
	_sprFuego->animarFrame(); /// animación del fuego en el menú principal.
}


void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_sprFondo, states);
	target.draw(_gameTitle, states);
	target.draw(*_sprFuego, states);
	for (int i = 0; i < std::size(_vButtons); i++) {
		target.draw(_vButtons[i], states);
	}
}

bool* Menu::getOpcMenuPress()
{
	return _vOpcMenuPress;
}

sf::Sprite& Menu::getSprFondo()
{
	return _sprFondo;
}

sf::Sprite& Menu::getSprCamino()
{
	return _sprCaminoDun;
}

sf::Sprite& Menu::getSprControles()
{
	return _sprControles;
}

Sprite* Menu::getSprFuego()
{
	return _sprFuego;
}

sf::Sound& Menu::getSonidoTeclas()
{
	return _soundTeclas;
}


