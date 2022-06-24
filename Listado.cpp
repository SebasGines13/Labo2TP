#include "Listado.h"

Listado::Listado()
{
    _fuente = new sf::Font;
    _fuente->loadFromFile("font/CELTG.ttf");
    _textTitulo  = new sf::Text;
    _textFinal   = new sf::Text;
    _textTitulo->setFont(*_fuente);
    _textFinal->setFont(*_fuente);
    _textTitulo->setFillColor(sf::Color(255, 255, 255, 220));
    _textTitulo->setCharacterSize(55);
    _textTitulo->setPosition(10.f, 100.f);
    _textTitulo->setString("RANKING TOP 5:");
    _textFinal->setString("Presione la tecla 'ESPACIO' para continuar...");
    _textFinal->setPosition(50.f, 600.f);
    for (int i = 0;i < std::size(_textRanking);i++) {
        _textRanking[i].setFont(*_fuente);
        _textRanking[i].setOrigin(_textRanking[i].getGlobalBounds().width / 2, _textRanking[i].getGlobalBounds().height / 2);
        _textRanking[i].setFillColor(sf::Color(255, 255, 255, 180));
        _textRanking[i].setCharacterSize(40);
        _textRanking[i].setPosition(50.f, 200.f + (i * 60));
    }    
}

Listado::~Listado()
{
    delete _textRanking;
    delete _textTitulo;
    delete _textFinal;
    delete _fuente;
}

void Listado::listarRanking() {
    int cantReg = cantidadRegistrosRanking();
    Ranking* vRanking;
    vRanking = new Ranking[cantReg];
    if (vRanking == NULL) {
        return;
    }
    cargarRanking(vRanking, cantReg); /// método para cargar el vector dinámico de rankings y ordenarlo
    int vueltas;
    if (cantReg > 5) vueltas = 5;
    else vueltas = cantReg;

    for (int i = 0; i < 5;i++) {
        _textRanking[i].setString("#" + std::to_string(i + 1) + ": " );
    }
    for (int i = 0; i < vueltas;i++) {
         _textRanking[i].setString("#" + std::to_string(i + 1) + ": " + std::to_string(vRanking[i].getPuntaje()) +" puntos - " + vRanking[i].getJugador());
    }
    delete []vRanking;
}


void Listado::cargarRanking(Ranking *v, int tam)
{
    Ranking reg; // Variable auxiliar para lectura de registros del archivo de ranking
    for (int i = 0;i < tam;i++) {
        v[i].LeerDeDisco(i);
    }
    for (int i = 0; i < tam;i++) {
        for (int j = i+1 ;j < tam;j++) {
            if (v[i].getPuntaje() < v[j].getPuntaje()) {
                reg = v[i];
                v[i] = v[j];
                v[j] = reg;
            }
        }
    }
}


int Listado::cantidadRegistrosRanking() {
    std::FILE* p = std::fopen("ranking.dat", "rb");
    if (p == NULL) {
        return 0;
    }
    size_t bytes;
    int cant_reg;
    std::fseek(p, 0, SEEK_END);
    bytes = std::ftell(p);
    std::fclose(p);
    cant_reg = bytes / sizeof(Ranking);
    return cant_reg;
}

void Listado::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(*_textTitulo, states);
    for (int i = 0; i < 5;i++) {
        target.draw(_textRanking[i], states);
    }
    target.draw(*_textFinal, states);
}

