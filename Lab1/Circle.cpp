#include "Circle.h"
#include <iostream>

const std::string Circle::DEFAULT_COLOR = "black";

Circle::Circle(int x, int y, int r) : Circle(x, y, r, DEFAULT_COLOR) {}

Circle::Circle(int x, int y, int r, const std::string& color) 
    : center(x, y), r(r), color(color) {}

Circle::Circle(const Circle& c) : Circle(c.getX(), c.getY(), c.getR(), c.getColor()) {}

int Circle::getR() const { return r; }
void Circle::setR(int r) { this->r = r; }
int Circle::getX() const { return center.getX(); }
void Circle::setX(int x) { center.setX(x); }
int Circle::getY() const { return center.getY(); }
void Circle::setY(int y) { center.setY(y); }
std::string Circle::getColor() const { return color; }
void Circle::setColor(const std::string& color) { this->color = color; }

Circle* Circle::clone() const {
    return new Circle(*this);
}

void Circle::draw() const {
    std::cout << "Circle (" << getX() << ", " << getY() << ") R: " << getR() << " " << getColor() << "\n";
}
