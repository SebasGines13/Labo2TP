#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Sprite.h"
 
class Menu: public sf::Drawable, public sf::Transformable
{
private:
	sf::Font	_font;
	sf::Text	_gameTitle;
	sf::Text	_vButtons[5];
	sf::Texture _txtFondo;
	sf::Texture _txtFuego;
	sf::Sprite	_sprFondo;
	Sprite*		_sprFuego;
	bool		_vOpcMenuSelect[5] = {true, false, false, false, false };
	bool		_vOpcMenuPress[5]  = {false, false, false, false, false };
public:
	enum class OpcMenu {Play, Ranking, Config, Credit , Exit};
	Menu();
	void command();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del método draw en Drawable.
	bool* getOpcMenuPress();
};

