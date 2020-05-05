#include "Button.h"
DPDrawing::Button::Button(int posX, int posY, SDL_Color bg_color, SDL_Color fg_color, string text) {
	SDL_Log("Creating Button %s", text.c_str());
    this->posX = posX;
    this->posY = posY;
	this->text = text;
	Uint16 t[text.length()];
	TTF_Font* font = TTF_OpenFont("resources/fonts/open-sans/OpenSans-Regular.ttf", 96);
	this->font = font;
	if(!font) {
		SDL_Log("ERROR: cannot find font");
	}
	SDL_Log("Converting string to Uint16...");
	SDL_Log("Setting rectangle...");
	this->rect = Rectangle(posX, posY, 110, 60);
	SDL_Log("Creating label...");
	this->label = TTF_RenderUTF8_Blended(font, text.c_str(), fg_color);
	//SDL_Log("Freeing label surface...");
	//SDL_FreeSurface(label);
	SDL_Log("Button initialized.");
}

float DPDrawing::Button::getArea() {
	return rect.getWidth() * rect.getHeight();
}

SDL_Rect* DPDrawing::Button::getRectangle() {
	return rect.getSDLObj();
}

SDL_Surface* DPDrawing::Button::getSurface() {
	return label;
}
