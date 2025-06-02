#pragma once
#include <string>

class GraphObject {
public:
    static const std::string DEFAULT_COLOR;
    
    virtual ~GraphObject() = default;
    virtual void draw() const = 0;
    virtual GraphObject* clone() const = 0;
};
