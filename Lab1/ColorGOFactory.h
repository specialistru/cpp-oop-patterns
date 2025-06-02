#pragma once
#include "AbstractGOFactory.h"
#include "Point.h"

class ColorGOFactory : public AbstractGOFactory {
public:
    static Point* const DEFAULT_POINT;
    
    Point* createPoint() override;
    Circle* createCircle() override;
};
