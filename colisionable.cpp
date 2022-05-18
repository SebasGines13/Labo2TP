#include "colisionable.h"

bool colisionable::isCollision(colisionable& obj)
{
    return getBounds().intersects(obj.getBounds());
}
