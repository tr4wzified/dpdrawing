#include "Shape.h"
void DPDrawing::Shape::setPosX(int posX) {
	this->posX = posX;
}

void DPDrawing::Shape::setPosY(int posY) {
	this->posY = posY;
}

void DPDrawing::Shape::setWidth(int width) {
	this->width = width;
}

void DPDrawing::Shape::setHeight(int height) {
	this->height = height;
}

int DPDrawing::Shape::getPosX() {
	return posX;
}

int DPDrawing::Shape::getPosY() {
	return posY;
}

int DPDrawing::Shape::getWidth() {
	return width;
}

int DPDrawing::Shape::getHeight() {
	return height;
}
