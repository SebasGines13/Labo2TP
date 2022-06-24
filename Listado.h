#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Ranking.h"

class Listado: public sf::Drawable, public sf::Transformable
{
	public:
		Listado();
		~Listado();
		void listarRanking();
		void cargarRanking(Ranking* v, int tam);
		int  cantidadRegistrosRanking();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::Font* _fuente;
		sf::Text* _textTitulo;
		sf::Text* _textFinal;
		sf::Text  _textRanking[5];
};

