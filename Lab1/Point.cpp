#include "Point.h"
#include <iostream>

Point::Point(int x, int y) : Point(x, y, GraphObject::DEFAULT_COLOR) {}

Point::Point(int x, int y, const std::string& color) : BWPoint(x, y), color(color) {}

Point::Point(const Point& p) : Point(p.getX(), p.getY(), p.getColor()) {}

Point* Point::clone() const {
    return new Point(*this);
}

void Point::draw() const {
    std::cout << "Point (" << getX() << ", " << getY() << ") " << getColor() << "\n";
}

std::string Point::getColor() const { return color; }
void Point::setColor(const std::string& color) { this->color = color; }
