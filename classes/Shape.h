#pragma once
namespace DPDrawing {
class Shape {
public:
    virtual float getArea() = 0;
    void setWidth(int width);
    void setHeight(int height);
    void setPosX(int posX);
    void setPosY(int posY);
    int width;
    int height;
    int posX;
    int posY;
};
}
