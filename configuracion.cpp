#include "Configuracion.h"

Configuracion::Configuracion()
{
	_buffer.loadFromFile("audio/teclas_menu.wav");
	_soundTeclas.setBuffer(_buffer);
	_soundTeclas.setVolume(40.f);
	_fuente = new sf::Font;
    _fuente->loadFromFile("font/CELTG.ttf");
    _textTitulo = new sf::Text;
    _textFinal = new sf::Text;
	_textMusica = new sf::Text;
	_textDificultad = new sf::Text;
    _textTitulo->setFont(*_fuente);
    _textFinal->setFont(*_fuente);
	_textMusica->setFont(*_fuente);
	_textDificultad->setFont(*_fuente);

    _textTitulo->setFillColor(sf::Color(255, 255, 255, 220));
	_textDificultad->setFillColor(sf::Color(255, 255, 255, 220));
	_textMusica->setFillColor(sf::Color(255, 255, 255, 220));
	_textFinal->setFillColor(sf::Color(255, 255, 255, 220));

    _textTitulo->setCharacterSize(100);
	_textTitulo->setCharacterSize(50);
	_textTitulo->setCharacterSize(50);
	_textTitulo->setCharacterSize(50);

    _textTitulo->setPosition(10.f, 100.f);
	_textDificultad->setPosition(10.f, 250.f);
	_textMusica->setPosition(80.f, 400.f);
	_textFinal->setPosition(50.f, 600.f);

    _textTitulo->setString("CONFIGURACION:");
	_textDificultad->setString("DIFICULTAD:");
	_textMusica->setString("MUSICA:");
    _textFinal->setString("Presione la tecla 'ESPACIO' para continuar...");

	_coolDown = 4;

    for (int i = 0;i < std::size(_vButtons);i++) {
		_vButtons[i].setFont(*_fuente);
		_vButtons[i].setOrigin(_vButtons[i].getGlobalBounds().width / 2, _vButtons[i].getGlobalBounds().height / 2);
		_vButtons[i].setFillColor(sf::Color(255, 255, 255, 180));
		_vButtons[i].setCharacterSize(30);
		switch (i)
		{
		case 0:
			_vButtons[i].setString("Facil");
			_vButtons[i].setPosition(300.f + (i * 140), 250.f);
			break;
		case 1:
			_vButtons[i].setString("Medio");
			_vButtons[i].setPosition(300.f + (i * 140), 250.f);
			break;
		case 2:
			_vButtons[i].setString("Dificil");
			_vButtons[i].setPosition(300.f + (i * 140), 250.f);
			break;
		case 3:
			_vButtons[i].setString("Si");
			_vButtons[i].setPosition(300.f, 400.f);
			break;
		case 4:
			_vButtons[i].setString("No");
			_vButtons[i].setPosition(300.f, 450.f);
			break;
		}
    }
}

Configuracion::~Configuracion()
{
    delete _textTitulo;
    delete _textFinal;
	delete _textMusica;
	delete _textDificultad;
    delete _fuente;
}

void Configuracion::menu(bool& bMusica, int& dificultad) {
	command();
	update(bMusica, dificultad);
}

void Configuracion::command() { /// Segun las teclas presionadas, se indica la selcción.


	if (_coolDown < 0) {
		_coolDown = 4;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
			_soundTeclas.play();
			if (_vOpcMenuSelect[(int)OpcMenu::Si]) {
				_vOpcMenuSelect[(int)OpcMenu::Si] = false;
				_vOpcMenuSelect[(int)OpcMenu::No] = true;
			}
			else if (_vOpcMenuSelect[(int)OpcMenu::No]) {
				_vOpcMenuSelect[(int)OpcMenu::No] = false;
				_vOpcMenuSelect[(int)OpcMenu::Si] = true;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
			_soundTeclas.play();
			if (_vOpcMenuSelect[(int)OpcMenu::Facil]) {
				_vOpcMenuSelect[(int)OpcMenu::Facil] = false;
				_vOpcMenuSelect[(int)OpcMenu::Medio] = true;
			}
			else if (_vOpcMenuSelect[(int)OpcMenu::Medio]) {
				_vOpcMenuSelect[(int)OpcMenu::Medio] = false;
				_vOpcMenuSelect[(int)OpcMenu::Dificil] = true;
			}
			else if (_vOpcMenuSelect[(int)OpcMenu::Dificil]) {
				_vOpcMenuSelect[(int)OpcMenu::Dificil] = false;
				_vOpcMenuSelect[(int)OpcMenu::Facil] = true;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
			_soundTeclas.play();
			if (_vOpcMenuSelect[(int)OpcMenu::Facil]) {
				_vOpcMenuSelect[(int)OpcMenu::Facil] = false;
				_vOpcMenuSelect[(int)OpcMenu::Dificil] = true;
			}
			else if (_vOpcMenuSelect[(int)OpcMenu::Medio]) {
				_vOpcMenuSelect[(int)OpcMenu::Medio] = false;
				_vOpcMenuSelect[(int)OpcMenu::Facil] = true;
			}
			else if (_vOpcMenuSelect[(int)OpcMenu::Dificil]) {
				_vOpcMenuSelect[(int)OpcMenu::Dificil] = false;
				_vOpcMenuSelect[(int)OpcMenu::Medio] = true;
			}
		}
	} else 	_coolDown--;	
}

void Configuracion::update(bool &bMusica, int& dificultad)  /// Segun las teclas seleccionada, actualizo colores y tamaño de los botones
{
	if (_vOpcMenuSelect[(int)OpcMenu::Si]) {
		_vButtons[(int)OpcMenu::Si].setFillColor(sf::Color::Yellow);
		_vButtons[(int)OpcMenu::Si].setScale(sf::Vector2f(1.25f, 1.25f));
		_vButtons[(int)OpcMenu::No].setFillColor(sf::Color(255, 255, 255, 128));
		_vButtons[(int)OpcMenu::No].setScale(sf::Vector2f(1.f, 1.f));
		bMusica = true;
	}
	else if (_vOpcMenuSelect[(int)OpcMenu::No]) {
		_vButtons[(int)OpcMenu::No].setFillColor(sf::Color::Yellow);
		_vButtons[(int)OpcMenu::No].setScale(sf::Vector2f(1.25f, 1.25f));
		_vButtons[(int)OpcMenu::Si].setFillColor(sf::Color(255, 255, 255, 180));
		_vButtons[(int)OpcMenu::Si].setScale(sf::Vector2f(1.f, 1.f));
		bMusica = false;
	}
	if (_vOpcMenuSelect[(int)OpcMenu::Facil]) {
		for (int i = 0; i < std::size(_vButtons)-2; i++) {
			_vButtons[i].setFillColor(sf::Color(255, 255, 255, 180));
			_vButtons[i].setScale(sf::Vector2f(1.f, 1.f));
		}
		_vButtons[(int)OpcMenu::Facil].setFillColor(sf::Color::Yellow);
		_vButtons[(int)OpcMenu::Facil].setScale(sf::Vector2f(1.25f, 1.25f));
		dificultad = 1;
	}
	else if (_vOpcMenuSelect[(int)OpcMenu::Medio]) {
		for (int i = 0; i < std::size(_vButtons)-2; i++) {
			_vButtons[i].setFillColor(sf::Color(255, 255, 255, 180));
			_vButtons[i].setScale(sf::Vector2f(1.f, 1.f));
		}
		_vButtons[(int)OpcMenu::Medio].setFillColor(sf::Color::Yellow);
		_vButtons[(int)OpcMenu::Medio].setScale(sf::Vector2f(1.25f, 1.25f));
		dificultad = 2;
	}
	else if (_vOpcMenuSelect[(int)OpcMenu::Dificil]) {
		for (int i = 0; i < std::size(_vButtons)-2; i++) {
			_vButtons[i].setFillColor(sf::Color(255, 255, 255, 180));
			_vButtons[i].setScale(sf::Vector2f(1.f, 1.f));
		}
		_vButtons[(int)OpcMenu::Dificil].setFillColor(sf::Color::Yellow);
		_vButtons[(int)OpcMenu::Dificil].setScale(sf::Vector2f(1.25f, 1.25f));
		dificultad = 3;
	}
}


void Configuracion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(*_textTitulo, states);
	target.draw(*_textDificultad, states);
	target.draw(*_textMusica, states);
	target.draw(*_textFinal, states);
    for (int i = 0; i < std::size(_vButtons);i++) {
        target.draw(_vButtons[i], states);
    }
    target.draw(*_textFinal, states);
}
