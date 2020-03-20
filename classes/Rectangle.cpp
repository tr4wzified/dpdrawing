#pragma once
#include "../main.h"
Rectangle::Rectangle(int width, int height, int posX, int posY) {
	this->width = width;
	this->height = height;
	this->posX = posX;
	this->posY = posY;
	rct = { posX, posY, width, height };
}

void Rectangle::setWidth(int width) {
	this->width = width;
	rct = { posX, posY, width, height };
}

void Rectangle::setWidth(int width) {
	this->width = width;
	rct = { posX, posY, width, height };
}

float Rectangle::getArea() {
	return width * height;
}

const SDL_Rect* Rectangle::getSDLObj() {
	return &rct;
}
