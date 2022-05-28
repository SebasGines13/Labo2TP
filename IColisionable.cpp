#include "IColisionable.h"

bool IColisionable::isCollision(IColisionable& obj)
{
    return getBounds().intersects(obj.getBounds());
}
