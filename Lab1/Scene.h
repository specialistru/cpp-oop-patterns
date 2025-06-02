#pragma once
#include <vector>
#include <memory>

class GraphObject;

class Scene {
private:
    std::vector<std::unique_ptr<GraphObject>> objects;
    static Scene instance;
    
    Scene();
    
public:
    static Scene& getInstance();
    
    void add(GraphObject* o);
    void clear();
    void draw() const;
    
    // Prevent copying
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
};
