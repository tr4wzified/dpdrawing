#pragma once
#include "Shape.h"
#include <SDL2/SDL.h>
namespace DPDrawing {
class Rectangle : public Shape {
public:
    Rectangle(int width, int height, int posX, int posY);
    void setWidth(int width);
    void setHeight(int height);
    void setPosX(int posX);
    void setPosY(int posY);
    float getArea();
    SDL_Rect* getSDLObj();
    void setRect(int mouseX, int mouseY, int mouseEndX, int mouseEndY);
    SDL_Rect rect;
};
}
