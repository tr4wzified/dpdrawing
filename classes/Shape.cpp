#include "Shape.h"

int DPDrawing::Shape::getWidth() {
	return this->width;
}

int DPDrawing::Shape::getHeight() {
	return this->height;
}

int DPDrawing::Shape::getPosX() {
	return this->posX;
}

int DPDrawing::Shape::getPosY() {
	return this->posY;
}

void DPDrawing::Shape::setWidth(int width) {
	this->width = width;
}

void DPDrawing::Shape::setHeight(int height) {
	this->height = height;
}

void DPDrawing::Shape::setPosX(int posX) {
	this->posX = posX;
}

void DPDrawing::Shape::setPosY(int posY) {
	this->posY = posY;
}
