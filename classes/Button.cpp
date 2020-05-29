#include "Button.h"
DPDrawing::Button::Button(int posX, int posY, SDL_Color& fg_color, int text, TTF_Font*& font) {
	if(!font) {
		SDL_Log("ERROR: cannot find font!");
	}
	this->rect = Rectangle(75, 75, posX, posY);
	this->label = TTF_RenderGlyph_Blended(font, text, fg_color);
}

SDL_Rect* DPDrawing::Button::getRectangle() {
	return rect.getSDLObj();
}

SDL_Surface*& DPDrawing::Button::getSurface() {
	return label;
}
