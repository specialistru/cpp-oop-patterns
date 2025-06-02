#pragma once
#include "GraphObject.h"
#include "Coords.h"

class Circle : public GraphObject {
private:
    Coords center;
    int r;
    std::string color;
    
public:
    static const std::string DEFAULT_COLOR;
    
    Circle(int x, int y, int r);
    Circle(int x, int y, int r, const std::string& color);
    Circle(const Circle& c);
    
    int getR() const;
    void setR(int r);
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    std::string getColor() const;
    void setColor(const std::string& color);
    
    Circle* clone() const override;
    void draw() const override;
};
