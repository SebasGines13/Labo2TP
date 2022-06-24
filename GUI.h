#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

class GUI: public sf::Drawable, public sf::Transformable
{
	public:
		// Constructor
		GUI(int cantVidas);
		// Destructor
		~GUI();
		/// Métodos
		void		 restarVida(int vida);
		void		 sumarPuntos(int puntos);
		const int	 getVidasRestantes();
		const int	 getPuntaje();
		void		 draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::Texture* _txtVida;
		sf::Sprite*  _sprVida;
		int			 _cantVidaInicial;
		int			 _cantVidaRestante;
		sf::Font*	 _fuente;
		sf::Text*	 _textPuntaje;
		sf::Text*	 _textVida;
		int			 _puntaje;
};

