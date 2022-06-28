#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

class GUI: public sf::Drawable, public sf::Transformable
{
	public:
		// Constructor
		GUI(int vidas);
		// Destructor
		~GUI();
		/// M�todos
		void		 update();
		void		 restarVida(int vida);
		void		 sumarPuntos(int puntos, int dificultad);
		const int	 getVidasRestantes();
		const int	 getPuntaje();
		void		 draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		bool		 esTiempoJefe();
	private:
		const int	 TIEMPOJEFE = 100;
		sf::Texture* _txtVida;
		sf::Sprite*  _sprVida;
		int			 _cantVidaInicial;
		int			 _cantVidaRestante;
		int			 _puntaje;
		sf::Font*	 _fuente;
		sf::Text*	 _textPuntaje;
		sf::Text*	 _textVida;
		sf::Text*	 _textTiempo;
		sf::Clock	 _clock; /// reloj 
};

