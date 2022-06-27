#pragma once
#include <SFML/Graphics.hpp>

class Sprite: public sf::Drawable, public sf::Transformable
{
	private:
		sf::Texture*   _textura; ///textura de Sfml
		sf::Sprite*	   _sprite; ///sprite de Sfml
		int			   _cantX; // Cantidad de frames en el eje x
		int		       _cantY; // Cantidad de frames en el eje y
		sf::Vector2f   _frameSize; //Tamaño del frame.
		sf::Vector2f   _frameActual; //Frame Actual.
		float	       _velAnima; // Velocidad del cambio de frame para la animación
	public:
		//Constructor
		Sprite(int sprClase, int cantX, int cantY, sf::Vector2f frameActual, float velAnima); 
		Sprite();
		/// Primero recibo el nro. para completar el nombre del archivo imagen a dibujar, luego la cantidad de animaciones/sprites en el nivel x, luego en el nivel y, la posición inicial y por último la velocidad de animación.
		//Destructor
		~Sprite();
		//sets
		void setPosicion(sf::Vector2f position);	
		void setFrameX(float frame);
		void setFrameY(float frame);
		//gets
		sf::Sprite	 getSprite();
		sf::Vector2f getFrameSize();
		//métodos
		void seleccionarFrame();
		void animar();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 
		void setColor(sf::Color color);
};

