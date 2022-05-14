#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class sprite
{
	private:
		Texture*   _txtPersonaje; ///textura del personaje
		Sprite*	   _sprPersonaje; ///sprite del personaje
		int		   _sprActual; /// Nro de sprite actual		
		int		   _cantX; // Cantidad de frames en el eje x
		int		   _cantY; // Cantidad de frames en el eje y
		Vector2f   _frameSize; //Tamaño del frame.
		Vector2f   _frameActual; //Frame Actual.
	public:
		//Constructor
		sprite(int sprClase, int cantX, int cantY, Vector2f frameActual);
		//sets
		void setPosicion(Vector2f position);
		void setCantX(int cantX);
		void setCantY(int cantY);		
		void setFrameSize(Vector2f frameSize);
		void setFrameActual(Vector2f frameActual);
		void setFrameX(int frame);
		void setFrameY(int frame);
		//gets
		Sprite getSprite();		
		Vector2f getFrameActual();
		Vector2f getFrameSize();
		Vector2f getPosicion();
		int getCantX();
		int getCantY();		
		int getFrameX();
		int getFrameY();
		//métodos
		void seleccionarFrame();
		void animarFrame();
};

