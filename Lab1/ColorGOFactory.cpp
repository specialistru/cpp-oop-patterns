#include "ColorGOFactory.h"
#include "Scene.h"

Point* const ColorGOFactory::DEFAULT_POINT = new Point(0, 0);

Point* ColorGOFactory::createPoint() {
    auto p = DEFAULT_POINT->clone();
    Scene::getInstance().add(p);
    return p;
}

Circle* ColorGOFactory::createCircle() {
    auto c = new Circle(0, 0, 1);
    Scene::getInstance().add(c);
    return c;
}
