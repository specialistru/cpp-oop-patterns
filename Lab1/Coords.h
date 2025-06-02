#pragma once

class Coords {
private:
    int x, y;
    
public:
    Coords(int x, int y);
    
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
};
