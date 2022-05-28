#include "Menu.h"

Menu::Menu()
{
	_font.loadFromFile("font/Metamorphous-Regular.ttf");
	//_font.loadFromFile("font/PressStart2P-Regular.ttf");
	//_font.loadFromFile("font/HiMelody-Regular.ttf");
	//_font.loadFromFile("font/BowlbyOneSC-Regular.ttf");
	_gameTitle.setFont(_font);
	_gameTitle.setString("Dungeon++");
	_gameTitle.setCharacterSize(100);
	_gameTitle.setFillColor(sf::Color(255, 255, 255, 128));
	_gameTitle.setOrigin(_gameTitle.getGlobalBounds().width / 2, _gameTitle.getGlobalBounds().height / 2);
	_gameTitle.setPosition(400.f, 250.f);
	_txtFondo.loadFromFile("img/dungeon_menu.png");
	_txtFondo.setSmooth(true);
	_sprFondo.setTexture(_txtFondo);
	_sprFondo.setColor(sf::Color(255, 255, 255, 150));
	_sprFuego = new Sprite(17, 75, 1, sf::Vector2f(0,0), 2.f);
	_sprFuego->setPosicion(sf::Vector2f(550.f,5.f));

	for (int i = 0; i < std::size(_vButtons); i++) {
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

void Menu::command() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
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
		if (_vOpcMenuSelect[(int)OpcMenu::Play]) {
			_vOpcMenuPress[(int)OpcMenu::Play]    = true;
			_vOpcMenuPress[(int)OpcMenu::Ranking] = false;
			_vOpcMenuPress[(int)OpcMenu::Config]  = false;
			_vOpcMenuPress[(int)OpcMenu::Credit]  = false;
			_vOpcMenuPress[(int)OpcMenu::Exit]	  = false;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Ranking]) {
			_vOpcMenuPress[(int)OpcMenu::Play]    = false;
			_vOpcMenuPress[(int)OpcMenu::Ranking] = true;
			_vOpcMenuPress[(int)OpcMenu::Config]  = false;
			_vOpcMenuPress[(int)OpcMenu::Credit]  = false;
			_vOpcMenuPress[(int)OpcMenu::Exit]    = false;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Config]) {
			_vOpcMenuPress[(int)OpcMenu::Play]    = false;
			_vOpcMenuPress[(int)OpcMenu::Ranking] = false;
			_vOpcMenuPress[(int)OpcMenu::Config]  = true;
			_vOpcMenuPress[(int)OpcMenu::Credit]  = false;
			_vOpcMenuPress[(int)OpcMenu::Exit]    = false;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Credit]) {
			_vOpcMenuPress[(int)OpcMenu::Play]    = false;
			_vOpcMenuPress[(int)OpcMenu::Ranking] = false;
			_vOpcMenuPress[(int)OpcMenu::Config]  = false;
			_vOpcMenuPress[(int)OpcMenu::Credit]  = true;
			_vOpcMenuPress[(int)OpcMenu::Exit]    = false;
		}
		else if (_vOpcMenuSelect[(int)OpcMenu::Exit]) {
			_vOpcMenuPress[(int)OpcMenu::Play]    = false;
			_vOpcMenuPress[(int)OpcMenu::Ranking] = false;
			_vOpcMenuPress[(int)OpcMenu::Config]  = false;
			_vOpcMenuPress[(int)OpcMenu::Credit]  = false;
			_vOpcMenuPress[(int)OpcMenu::Exit]    = true;
		}
	}
}


void Menu::update() 
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
	_sprFuego->animarFrame();
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
