#include "Rectangle.h"
DPDrawing::Rectangle::Rectangle(int width, int height, int posX, int posY) {
	this->setWidth(width);
	this->setHeight(height);
	this->setPosX(posX);
	this->setPosY(posY);
}

float DPDrawing::Rectangle::getArea() {
    return this->getWidth() * this->getHeight();
}

string DPDrawing::Rectangle::getType() {
	return "Rectangle";
}

SDL_Rect* DPDrawing::Rectangle::getSDLObj() {
	rect.x = this->getPosX();
	rect.y = this->getPosY();
	rect.w = this->getWidth();
	rect.h = this->getHeight();
    return &this->rect;
}
