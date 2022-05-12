#pragma once
#include "SFML\Graphics.hpp"
using namespace sf;

class mapa
{
private:
	Texture* _txtMapa; ///textura del mapa
	Sprite*  _sprMapa; ///sprite del mapa
	int		 _sprActual; /// Nro de sprite actual		
public:
	mapa(int sprClase); /// Constructor
	Sprite getSprite(); /// Obtengo el sprite del mapa
};

