#pragma once
#include "Shape.h"
#include <SDL2/SDL.h>
namespace DPDrawing {
class Rectangle : public Shape {
public:
    Rectangle(int width, int height, int posX, int posY);
    float getArea();
    SDL_Rect* getSDLObj();
	string getType();
private:
    SDL_Rect rect;
};
}
