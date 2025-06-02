#include "Scene.h"
#include "GraphObject.h"

Scene Scene::instance;

Scene::Scene() {}

Scene& Scene::getInstance() {
    return instance;
}

void Scene::add(GraphObject* o) {
    objects.emplace_back(o);
}

void Scene::clear() {
    objects.clear();
}

void Scene::draw() const {
    for (const auto& obj : objects) {
        obj->draw();
    }
}
