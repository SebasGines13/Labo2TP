#pragma once
#include <cstring>
#include <iostream>

class Ranking
{
	public:
		void setJugador(std::string jugador);
		void setPuntaje(const int& puntaje);
		std::string getJugador();
		int	 getPuntaje();
		bool GuardarEnDisco();
		bool LeerDeDisco(int nroRegistro);
	private:
		char  _jugador[5];
		int	  _puntaje;
};

