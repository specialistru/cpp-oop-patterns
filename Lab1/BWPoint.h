#pragma once
#include "GraphObject.h"
#include "Coords.h"

class BWPoint : public GraphObject {
private:
    Coords coords;
    
public:
    BWPoint(int x, int y);
    BWPoint(const BWPoint& p);
    
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    
    BWPoint* clone() const override;
    void draw() const override;
};
