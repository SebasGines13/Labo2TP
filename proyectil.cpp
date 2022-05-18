#include "proyectil.h"
using namespace std;


///Constructor
proyectil::proyectil(Vector2f posicion) {
    _sprProyectil = new sprite(13, 5, 1, Vector2f(0, 0), .5f);
    _velDesplaz = 10.f;
    _velocidad = Vector2f(0, 0);
    respawn(posicion);
}


sprite proyectil::getSprite()
{
    return *_sprProyectil;
}

void proyectil::animar() {
    _sprProyectil->animarFrame();
}

void proyectil::setVelocidad(Vector2f vel)
{
    _velocidad += vel;
}

void proyectil::update() {
    _sprProyectil->setPosicion(Vector2f(_sprProyectil->getPosicion().x + _velDesplaz, _sprProyectil->getPosicion().y));
    animar();   
}


void proyectil::respawn(Vector2f posicion) {
    _sprProyectil->setPosicion(posicion);
}

FloatRect proyectil::getBounds()
{
    return _sprProyectil->getSprite().getGlobalBounds();
}
