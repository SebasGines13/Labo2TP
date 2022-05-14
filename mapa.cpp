#include "mapa.h"
#include <iostream>
using namespace std;

///Constructor
mapa::mapa(int sprClase, int tilewidth, int tileheight) {
    String path = "img/mapa" + to_string(sprClase) + ".jpg"; //contruyo la ruta para conocer la imagen actual del mapa.
    _sprActual = sprClase; //nro del sprite actual
    _txtMapa = new Texture();
    _txtMapa->loadFromFile(path);
    _sprMapa = new Sprite(*_txtMapa);
    _tilewidth = tilewidth;
    _tileheight = tileheight;
}

Sprite mapa::getSprite() {
    return *_sprMapa;
}

bool mapa::existeBloqueo(Vector2f casilla)
{   
    if (_mBorde[(int)casilla.y / _tilewidth][(int)casilla.x / _tileheight] == 1) {
        return true;
    }
    return false;
}