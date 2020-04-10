#include "Rocket.h"


Rocket::Rocket(int x, int y, int width, int height)
{
    position.x(x);
    position.y(y);
    this->width(width);
    this->height(height);
}

void Rocket::setRocket(int x, int y, int width, int height)
{
    position.x(x);
    position.y(y);
    this->width(width);
    this->height(height);
}
