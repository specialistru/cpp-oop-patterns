#include "BWPoint.h"
#include <iostream>

BWPoint::BWPoint(int x, int y) : coords(x, y) {}

BWPoint::BWPoint(const BWPoint& p) : BWPoint(p.getX(), p.getY()) {}

int BWPoint::getX() const { return coords.getX(); }
void BWPoint::setX(int x) { coords.setX(x); }
int BWPoint::getY() const { return coords.getY(); }
void BWPoint::setY(int y) { coords.setY(y); }

BWPoint* BWPoint::clone() const {
    return new BWPoint(*this);
}

void BWPoint::draw() const {
    std::cout << "BWPoint (" << getX() << ", " << getY() << ")\n";
}
