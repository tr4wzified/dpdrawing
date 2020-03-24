#include "Pixel.h"

DPDrawing::Pixel::Pixel(int posX, int posY, int r, int g, int b, int a) {
	this->posX = posX;
	this->posY = posY;
	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;
	this->color[3] = a;
}

/*
DPDrawing::Pixel::Pixel(int posX, int posY, int color[4]) {
	this->posX = posX;
	this->posY = posY;
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
	this->color[3] = color[3];
}
*/

int DPDrawing::Pixel::Draw(SDL_Renderer*& renderer) {
	SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
	SDL_RenderDrawPoint(renderer, posX, posY);
	SDL_RenderPresent(renderer);
	return 0;
}
