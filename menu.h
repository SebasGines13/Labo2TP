#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>
#include "Sprite.h"
 
class Menu: public sf::Drawable, public sf::Transformable
{
private:
	sf::Font	_font;
	sf::Text	_gameTitle;
	sf::Text	_vButtons[5];
	sf::Texture _txtFondo;
	sf::Texture _txtFuego;
	sf::Texture _txtControles;
	sf::Sprite	_sprFondo;
	sf::Sprite	_sprControles;
	Sprite*		_sprFuego;
	sf::SoundBuffer     _buffer;  /// buffer para el sonido
	sf::Sound           _soundTeclas;   /// canal utilizado por el buffer
	bool		_vOpcMenuSelect[5] = {true, false, false, false, false };
	bool		_vOpcMenuPress[5]  = {false, false, false, false, false };
public:
	enum class OpcMenu {Play, Ranking, Config, Credit , Exit};
	Menu();
	void command();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
	bool* getOpcMenuPress();
	sf::Sprite& getImgControles();
	sf::Sound& getSonidoTeclas();
};

