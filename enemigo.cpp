#include "enemigo.h"
#include <stdlib.h>

enemigo::enemigo(Vector2f posicion) {
    std::string path;
    path = "img/zombie1.png";
    txtMonster.loadFromFile(path);
    sprMonster.setTexture(txtMonster);
    sprMonster.setPosition(posicion);
}

Sprite enemigo::getSprite() {
    return sprMonster;
}


