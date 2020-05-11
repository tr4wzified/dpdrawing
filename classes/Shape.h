#pragma once
#include <SDL2/SDL.h>
namespace DPDrawing {
class Shape {
public:
    virtual float getArea() = 0;
    virtual void setWidth(int width);
    void setHeight(int height);
	int getWidth();
	int getHeight();
	int getPosX();
	int getPosY();
    void setPosX(int posX);
    void setPosY(int posY);
    int width;
    int height;
    int posX;
    int posY;
};
}
