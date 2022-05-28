#include "Mapa.h"
#include "BloqueSolido.h"

///Constructor
Mapa::Mapa(int sprClase, int tilewidth, int tileheight, int mapwidth, int mapheight)
{
    std::string path = "img/mapa" + std::to_string(sprClase) + ".png"; //contruyo la ruta para conocer la imagen actual del mapa.
    _sprActual = sprClase; //nro del sprite actual
    _txtMapa = new sf::Texture();
    _txtMapa->loadFromFile(path);
    _tilewidth = tilewidth;
    _tileheight = tileheight;
    _mapWidth = mapwidth;
    _mapHeight = mapheight;
    int i = 0;
    Bloque* pBloque = nullptr;
    for (int f = 0; f < _mapHeight; f++) { 
        for (int c = 0; c < _mapWidth; c++) { 
            int columnas = _txtMapa->getSize().x / _tilewidth;
            int id = _vMapa[i]-1;
            int xAux = id % columnas;
            int yAux = id / columnas;
            switch (_vMapa[i++])
            {
            case 34: case 35: case 36: case 62: case 98: case 99: case 100: case 114: case 115: case 116: case 110: case 184: case 167: case 168: case 183: case 185: case 182: case 186: case 181: case 50:
                pBloque = new BloqueSolido();
                break;
            case 171:
                _spawnPlayer.x = (float)c;
                _spawnPlayer.y = (float)f;
            default:
                pBloque = new Bloque();
                break;
            }
            pBloque->setTextureBloque(*_txtMapa);
            pBloque->setTextureRectBloque(sf::IntRect(xAux * _tilewidth, yAux * _tileheight, _tilewidth, _tileheight));
            pBloque->setPosition(sf::Vector2f((float)c*_tilewidth, (float)f*_tileheight));
            _bloques.push_back(pBloque);
        }
    }
}

void Mapa::draw(sf::RenderTarget& target, sf::RenderStates states) const
{    
    for (Bloque* pBloque : _bloques) {
        states.transform *= getTransform();
        target.draw(*pBloque, states);
    }    
}

sf::Vector2f Mapa::getPlayerSpawn() const
{
    return _spawnPlayer;
}

int Mapa::getTileWidth() const
{
    return _tilewidth;
}

int Mapa::getTilHeight() const
{
    return _tileheight;
}

std::vector<Bloque*> Mapa::getBloques() const
{
    return _bloques;
}
