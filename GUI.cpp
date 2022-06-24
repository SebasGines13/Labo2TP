#include "GUI.h"

GUI::GUI(int cantVida)
{
	_puntaje = 0;
	_fuente = new sf::Font;
	_fuente->loadFromFile("font/CELTG.ttf");
	_textPuntaje = new sf::Text;
	_textVida = new sf::Text;
	_textPuntaje->setFont(*_fuente);
	_textVida->setFont(*_fuente);
	_textVida->setString("Vidas:");
	_textPuntaje->setPosition(600.f, 15.f);
	_textVida->setPosition(10.f, 15.f);
	_textPuntaje->setCharacterSize(30);
	_textVida->setCharacterSize(30);
	_textPuntaje->setFillColor(sf::Color(255, 255, 255, 255));
	_textVida->setFillColor(sf::Color(255, 255, 255, 255));
	_txtVida = new sf::Texture;
	_txtVida->loadFromFile("img/itemCora.png");
	_sprVida = new sf::Sprite(*_txtVida);
	_cantVidaInicial = cantVida;
	_cantVidaRestante = _cantVidaInicial;
}

GUI::~GUI()
{
	delete _sprVida; 
	delete _txtVida;
	delete _textVida;
	delete _textPuntaje;
	delete _fuente;
}

void GUI::restarVida(int vida) 
{
	_cantVidaRestante -= vida;
}

void GUI::sumarPuntos(int puntos)
{
	_puntaje += puntos;
}

const int GUI::getVidasRestantes()
{
	return _cantVidaRestante;
}

const int GUI::getPuntaje()
{
	return _puntaje;
}

void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	_textPuntaje->setString("Puntos: " + std::to_string(_puntaje));
	target.draw(*_textPuntaje, states);
	target.draw(*_textVida, states);
	_sprVida->setPosition(_textVida->getGlobalBounds().width, _textVida->getGlobalBounds().top); /// Para que vuelva a dibujarse la cantidad de vidas desde la posición inicial en pantalla
	for (int i = 1; i <= _cantVidaInicial; i++) {
		if (i <= _cantVidaRestante) {
			_sprVida->setColor(sf::Color(255, 255, 255, 255));
		}
		else {
			_sprVida->setColor(sf::Color(255, 255, 255, 30));
		}
		_sprVida->move(_sprVida->getGlobalBounds().width, 0);
		target.draw(*_sprVida, states);
	}
	
	
}
