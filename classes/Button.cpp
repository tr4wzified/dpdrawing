#include "Button.h"
DPDrawing::Button::Button(int posX, int posY, SDL_Color fg_color, int text) {
    this->posX = posX;
    this->posY = posY;
	this->text = text;
	TTF_Font* font = TTF_OpenFont("resources/fonts/open-sans/OpenSans-Regular.ttf", 96);
	this->font = font;
	this->fg_color = fg_color;
	if(!font) {
		SDL_Log("ERROR: cannot find font");
	}
	SDL_Log("Setting rectangle...");
	this->rect = Rectangle(75, 75, posX, posY);
	SDL_Log("Creating label...");
	this->label = TTF_RenderGlyph_Blended(font, text, fg_color);
	SDL_Log("Button initialized.");
}

SDL_Rect* DPDrawing::Button::getRectangle() {
	return rect.getSDLObj();
}

SDL_Surface* DPDrawing::Button::getSurface() {
	return label;
}
