#pragma once
#include "Rectangle.h"
#include "Shape.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
using std::string;
namespace DPDrawing {
class Button {
public:
	Button(int posX, int posY, SDL_Color fg_color, int text);
	SDL_Rect* getRectangle();
	SDL_Surface* getSurface();
private:
	int posX;
	int posY;
    Rectangle rect = Rectangle(0,0,0,0);
    TTF_Font* font;
    string text;
	SDL_Surface* label;
	SDL_Color fg_color;

};
}
