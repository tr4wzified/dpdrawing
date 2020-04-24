#include "Button.h"
DPDrawing::Button::Button(int posX, int posY, TTF_Font* font, SDL_Color color, string text) {
    this->posX = posX;
    this->posY = posY;
    this->font = font;
	this->text = text;
	Uint16 t[text.length()];
	for(int i = 0; i < text.length(); i++) {
		t[i] = text[i];
	}
	this->rect = Rectangle(100, 200, posX, posY);
	this->label = TTF_RenderUNICODE_Blended(font, t, color);
}

float DPDrawing::Button::getArea() {
	return rect.getWidth() * rect.getHeight();
}

void DPDrawing::Button::Draw(SDL_Renderer* r) {
	const SDL_Rect* rect = this->rect.getSDLObj();
}
