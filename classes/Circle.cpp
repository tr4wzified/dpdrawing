#include "Circle.h"
DPDrawing::Circle::Circle(int width, int height, int posX, int posY) {
	setRadiusX(width / 2);
	setRadiusY(height / 2);
	setPosX(posX);
	setPosY(posY);
}

float DPDrawing::Circle::getArea() {
	return M_PI * this->radiusX * this->radiusY;
}

int DPDrawing::Circle::getRadiusX() {
	return this->radiusX;
}

int DPDrawing::Circle::getRadiusY() {
	return this->radiusY;
}

void DPDrawing::Circle::setRadiusX(int radiusX) {
	this->radiusX = radiusX;
	this->width = radiusX * 2;
}

void DPDrawing::Circle::setRadiusY(int radiusY) {
	this->radiusY = radiusY;
	this->height = radiusY * 2;
}
