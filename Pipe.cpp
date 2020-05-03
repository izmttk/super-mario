#include "Pipe.h"


void Pipe::setPipe(int x, int y, int width, int height)
{
    type("pipe");
    position.x(x);
    position.y(y);
    this->width(width);
    this->height(height);
}