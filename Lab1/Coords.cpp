#include "Coords.h"

Coords::Coords(int x, int y) : x(x), y(y) {}

int Coords::getX() const { return x; }
void Coords::setX(int x) { this->x = x; }
int Coords::getY() const { return y; }
void Coords::setY(int y) { this->y = y; }
