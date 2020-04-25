#include "Pipe.h"

Pipe::Pipe(int x, int y, int width, int height)
{
    position.x(x);
    position.y(y);
    this->width(width);
    this->height(height);
}

void Pipe::setPipe(int x, int y, int width, int height)
{
    position.x(x);
    position.y(y);
    this->width(width);
    this->height(height);
}