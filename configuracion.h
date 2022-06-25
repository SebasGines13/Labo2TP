#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Text.hpp>

class Configuracion: public sf::Drawable, public sf::Transformable
{
	public:
		enum class OpcMenu { Facil, Medio, Dificil, Si, No};
		Configuracion();
		~Configuracion();
		void command();
		void update(bool& bMusica, int& dificultad);
		void menu(bool& bMusica, int& dificultad);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::Font*		 _fuente;
		sf::Text*		 _textTitulo;
		sf::Text*		 _textFinal;
		sf::Text*		 _textMusica;
		sf::Text*		 _textDificultad;
		sf::Text		 _vButtons[5];
		sf::SoundBuffer  _buffer;  /// buffer para el sonido
		sf::Sound        _soundTeclas;   /// canal utilizado por el buffer
		bool			 _vOpcMenuSelect[5] = { true, false, false, true, false };
		bool			 _vOpcMenuPress[5] = { true, false, false, true, false };
		int				 _coolDown;
};

