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
	Button(int posX, int posY, TTF_Font* font, SDL_Color color, string text);
    Rectangle rect = Rectangle(1,1,1,1);
    TTF_Font* font;
    string text;
	SDL_Surface* label;
    float getArea();
	void Draw(SDL_Renderer* r);
};
}
