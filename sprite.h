#pragma once
#include <SFML/Graphics.hpp>

class sprite
{
	private:
		sf::Texture*   _txtPersonaje; ///textura del personaje
		sf::Sprite*	   _sprPersonaje; ///sprite del personaje
		int		   _sprActual; /// Nro de sprite actual		
		int		   _cantX; // Cantidad de frames en el eje x
		int		   _cantY; // Cantidad de frames en el eje y
		sf::Vector2f   _frameSize; //Tamaño del frame.
		sf::Vector2f   _frameActual; //Frame Actual.
		float	   _velAnima; // Velocidad del cambio de frame para la animación
	public:
		//Constructor
		sprite(int sprClase, int cantX, int cantY, sf::Vector2f frameActual, float velAnima);
		//sets
		void setPosicion(sf::Vector2f position);
		void setCantX(int cantX);
		void setCantY(int cantY);		
		void setFrameSize(sf::Vector2f frameSize);
		void setFrameActual(sf::Vector2f frameActual);
		void setFrameX(int frame);
		void setFrameY(int frame);
		//gets
		sf::Sprite getSprite();
		sf::Vector2f getFrameActual();
		sf::Vector2f getFrameSize();
		sf::Vector2f getPosicion();
		int getCantX();
		int getCantY();		
		int getFrameX();
		int getFrameY();
		//métodos
		void seleccionarFrame();
		void animarFrame();
};

