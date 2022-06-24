#include "ranking.h"

void Ranking::setJugador(std::string jugador)
{
	strcpy(_jugador, jugador.c_str());
}

void Ranking::setPuntaje(const int& puntaje)
{
	_puntaje = puntaje;
}

std::string  Ranking::getJugador()
{
    std::string jugador(_jugador);
    return jugador;
}

int Ranking::getPuntaje()
{
    return _puntaje;
}

bool Ranking::GuardarEnDisco()
{
    std::FILE* p = std::fopen("ranking.dat", "ab");
    if (p == NULL) {
        return false;
    }
    bool guardo = std::fwrite(this, sizeof(Ranking), 1, p);
    std::fclose(p);
    return guardo;
}

bool Ranking::LeerDeDisco(int nroRegistro)
{
    std::FILE* p = std::fopen("ranking.dat", "rb");
    if (p == NULL) {
        return false;
    }
    std::fseek(p, nroRegistro * sizeof(Ranking), SEEK_SET);
    bool ok = std::fread(this, sizeof(Ranking), 1, p);
    std::fclose(p);
    return ok;
}
