#include "Rectangle.h"
DPDrawing::Rectangle::Rectangle(int width, int height, int posX, int posY) {
	this->width = width;
	this->height = height;
	this->posX = posX;
	this->posY = posY;
	this->rect = { posX, posY, width, height };
}

void DPDrawing::Rectangle::setWidth(int width) {
	this->width = width;
	this->rect = { posX, posY, width, height };
}

void DPDrawing::Rectangle::setHeight(int height) {
	this->width = width;
	this->rect = { posX, posY, this->width, this->height };
}

float DPDrawing::Rectangle::getArea() {
	return this->width * this->height;
}

const SDL_Rect* DPDrawing::Rectangle::getSDLObj() {
	return &this->rect;
}
