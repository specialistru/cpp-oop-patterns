#pragma once
#include "BWPoint.h"

class Point : public BWPoint {
private:
    std::string color;
    
public:
    Point(int x, int y);
    Point(int x, int y, const std::string& color);
    Point(const Point& p);
    
    Point* clone() const override;
    void draw() const override;
    
    std::string getColor() const;
    void setColor(const std::string& color);
};
