#include "GUI.h"
#include <iomanip>

GUI::GUI(int vidas, int tiempoJefe)
{
	_puntaje = 0;
	_fuente = new sf::Font;
	_fuente->loadFromFile("font/CELTG.ttf");
	_textPuntaje = new sf::Text;
	_textVida = new sf::Text;
	_textTiempo = new sf::Text;
	_textPuntaje->setFont(*_fuente);
	_textVida->setFont(*_fuente);
	_textTiempo->setFont(*_fuente);
	_textVida->setString("Vidas:");
	_textPuntaje->setPosition(600.f, 15.f);
	_textVida->setPosition(10.f, 15.f);
	_textTiempo->setPosition(350.f, 15.f);
	_textPuntaje->setCharacterSize(30);
	_textVida->setCharacterSize(30);
	_textTiempo->setCharacterSize(30);
	_textPuntaje->setFillColor(sf::Color(255, 255, 255, 255));
	_textVida->setFillColor(sf::Color(255, 255, 255, 255));
	_textTiempo->setFillColor(sf::Color(255, 255, 255, 255));
	_txtVida = new sf::Texture;
	_txtVida->loadFromFile("img/itemCora.png");
	_sprVida = new sf::Sprite(*_txtVida);
	_cantVidaInicial = vidas; 
	_cantVidaRestante = _cantVidaInicial;
	_tiempoJefe = tiempoJefe;
	_tiempo = _tiempoJefe;
	_stopTiempo = false;
}

GUI::~GUI()
{
	delete _sprVida; 
	delete _txtVida;
	delete _textVida;
	delete _textPuntaje;
	delete _fuente;
}

void GUI::update()
{
	_tiempo = _tiempoJefe - _clock.getElapsedTime().asSeconds();
	if (_tiempo <= 0){
		if (_stopTiempo) _tiempo = 0;
		else _clock.restart();
	}
}

void GUI::reiniciarTiempo() {
	_tiempo = _tiempoJefe;
	_clock.restart();
}

void GUI::restarVida(int vida)
{
	_cantVidaRestante -= vida;
}

void GUI::sumarVida(int vida)
{
	_cantVidaRestante += vida;
	if (_cantVidaRestante > _cantVidaInicial) {
		_cantVidaRestante = _cantVidaInicial;
	}
}

void GUI::sumarPuntos(int puntos, int dificultad)
{
	_puntaje += (puntos*dificultad);
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
	_textTiempo->setString("Jefe en " + std::to_string(_tiempo));
	target.draw(*_textPuntaje, states);
	target.draw(*_textVida, states);
	target.draw(*_textTiempo, states);
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

bool GUI::esTiempoJefe()
{
	if (_tiempo > 0 || _stopTiempo) {
		return false;
	}
	return true;
}

void GUI::setStopTiempo(bool stopTiempo)
{
	_stopTiempo = stopTiempo;
	if (_stopTiempo) {
		_tiempo = 0;
	}else _clock.restart();
}
