#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>
#include "Sprite.h"
 
class Menu: public sf::Drawable, public sf::Transformable
{
	public:
		enum class OpcMenu {Play, Ranking, Config, Credit , Exit};
		/// Constructor
		Menu();
		/// Destructor
		~Menu();
		/// Gets
		bool*		getOpcMenuPress();
		sf::Sprite& getSprCamino();
		sf::Sprite& getSprControles();
		sf::Sprite& getSprFondo();
		Sprite*		getSprFuego();
		sf::Sound&	getSonidoTeclas();
		/// M�todos
		void		creditos();
		void		command();
		void		update();
		void		draw(sf::RenderTarget& target, sf::RenderStates states) const override; /// Polimorfismo del m�todo draw en Drawable.
	private:
		sf::Font		 _font;
		sf::Text		 _gameTitle;
		sf::Text		 _vCreditos[6];
		sf::Text		 _vButtons[5];
		sf::Texture		 _txtFondo;
		sf::Texture		 _txtFuego;
		sf::Texture		 _txtControles;
		sf::Texture		 _txtCaminoDun;
		sf::Sprite		 _sprFondo;
		sf::Sprite		 _sprControles;
		sf::Sprite		 _sprCaminoDun;
		Sprite*			 _sprFuego;
		sf::SoundBuffer  _buffer;  /// buffer para el sonido
		sf::Sound        _soundTeclas;   /// canal utilizado por el buffer
		bool			 _vOpcMenuSelect[5] = { true, false, false, false, false };
		bool			 _vOpcMenuPress[5] = { false, false, false, false, false };
		
};

