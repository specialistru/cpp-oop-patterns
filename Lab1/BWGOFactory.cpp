#include "BWGOFactory.h"
#include "Scene.h"

BWPoint* BWGOFactory::createPoint() {
    auto p = new BWPoint(1, 1);
    Scene::getInstance().add(p);
    return p;
}

Circle* BWGOFactory::createCircle() {
    auto c = new Circle(0, 0, 1);
    Scene::getInstance().add(c);
    return c;
}
