#pragma once
#include "Shape.h"
#include <SDL2/SDL.h>
namespace DPDrawing {
class Rectangle : public Shape {
public:
    Rectangle(int width, int height, int posX, int posY);
    float getArea();
    void setPosX(int posX);
    void setPosY(int posY);
    void setWidth(int width);
    void setHeight(int height);
	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
    SDL_Rect* getSDLObj();
    void setRect(int mouseX, int mouseY, int mouseEndX, int mouseEndY);
	string getType();
private:
    SDL_Rect rect;
	int width;
	int height;
	int posX;
	int posY;
};
}
