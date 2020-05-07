#pragma once
#include "Rectangle.h"
#include "Shape.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
using std::string;
namespace DPDrawing {
class Button : public Shape {
public:
	Button(int posX, int posY, SDL_Color bg_color, SDL_Color fg_color, int text);
    float getArea();
	SDL_Rect* getRectangle();
	SDL_Surface* getSurface();
private:
    Rectangle rect = Rectangle(0,0,0,0);
    TTF_Font* font;
    string text;
	SDL_Surface* label;
	SDL_Color bg_color;
	SDL_Color fg_color;

};
}
