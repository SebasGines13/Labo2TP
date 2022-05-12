#include "mapa.h"
using namespace std;

///Constructor
mapa::mapa(int sprClase) {
    String path = "img/mapa" + to_string(sprClase) + ".jpg"; //contruyo la ruta para conocer la imagen actual del mapa.
    _sprActual = sprClase; //nro del sprite actual
    _txtMapa = new Texture();
    _txtMapa->loadFromFile(path);
    _sprMapa = new Sprite(*_txtMapa);
}

Sprite mapa::getSprite() {
    return *_sprMapa;
}