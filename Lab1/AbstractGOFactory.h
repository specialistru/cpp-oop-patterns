#pragma once
#include "BWPoint.h"
#include "Circle.h"

class AbstractGOFactory {
public:
    virtual ~AbstractGOFactory() = default;
    virtual BWPoint* createPoint() = 0;
    virtual Circle* createCircle() = 0;
};
