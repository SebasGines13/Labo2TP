#include "mapa.h"

///Constructor
mapa::mapa(int sprClase, int tilewidth, int tileheight, int mapwidth, int mapheight) {
    std::string path = "img/mapa" + std::to_string(sprClase) + ".png"; //contruyo la ruta para conocer la imagen actual del mapa.
    _sprActual = sprClase; //nro del sprite actual
    _txtMapa = new sf::Texture();
    _txtMapa->loadFromFile(path);
    _tilewidth = tilewidth;
    _tileheight = tileheight;
    _mapWidth = mapwidth;
    _mapHeight = mapheight;
    cargar();
}


bool mapa::isCollision(colisionable& obj) {
    sf::FloatRect auxRect = obj.getBounds();
    for (int y = 0; y < _mapHeight; y++) {
        for (int x = 0; x < _mapWidth; x++) {     
            if (_tilemapSprite[x][y].getBounds().intersects(obj.getBounds()) && _tilemapSprite[x][y].esSolido()) {
                return true;
           }
        }
    }
    return false;
}


void mapa::cargar() 
{ 
    for (int y = 0; y < _mapHeight; y++) {
        for (int x = 0; x < _mapWidth; x++) { 
            _tilemapSprite[x][y].setTextureBloque(*_txtMapa);
            int id = _mapa[x][y]-2;
            if (id != -1) {
                int columnas = _txtMapa->getSize().x / _tilewidth;
                int xAux = id % columnas;
                int yAux = id / columnas;
                _tilemapSprite[x][y].setTextureRectBloque(sf::IntRect(xAux * _tilewidth, yAux * _tileheight, _tilewidth, _tileheight));
            }
            else {
                _tilemapSprite[x][y].setColorBloque(sf::Color::Black);
            }
            if (id != 6) { /// Si no es el piso, se establece bloqueado para el personaje.
                _tilemapSprite[x][y].setSolido(true);
            }
            _tilemapSprite[x][y].setPosition(sf::Vector2f((float)y * _tileheight, (float)x * _tilewidth));
        }
    }
}

void mapa::draw(sf::RenderTarget& target, sf::RenderStates states) const
{    
    for (int y = 0; y < _mapHeight; y++) {
        for (int x = 0; x < _mapWidth; x++) {
            states.transform *= getTransform();
            target.draw(_tilemapSprite[x][y], states);
        }
    }
}
