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

void DPDrawing::Circle::setPosX(int posX) {
	this->posX = posX;
}

void DPDrawing::Circle::setPosY(int posY) {
	this->posY = posY;
}

void DPDrawing::Circle::setWidth(int width) {
	this->width = width;
	this->radiusX = width / 2;
}

void DPDrawing::Circle::setHeight(int height) {
	this->height = height;
	this->radiusY = height / 2;
}

void DPDrawing::Circle::setRadiusX(int radiusX) {
	this->radiusX = radiusX;
	this->width = radiusX * 2;
}

void DPDrawing::Circle::setRadiusY(int radiusY) {
	this->radiusY = radiusY;
	this->height = radiusY * 2;
}

void DPDrawing::Circle::setCenterX(int centerX) {
	this->posX = centerX - getRadiusX();
}

void DPDrawing::Circle::setCenterY(int centerY) {
	this->posY = centerY - getRadiusY();
}

int DPDrawing::Circle::getPosX() {
	return this->posX;
}

int DPDrawing::Circle::getPosY() {
	return this->posY;
}

int DPDrawing::Circle::getWidth() {
	return this->width;
}

int DPDrawing::Circle::getHeight() {
	return this->height;
}

int DPDrawing::Circle::getCenterX() {
	return this->posX + getRadiusX();
}

int DPDrawing::Circle::getCenterY() {
	return this->posY + getRadiusY();
}

int DPDrawing::Circle::getRadiusX() {
	return this->radiusX;
}

int DPDrawing::Circle::getRadiusY() {
	return this->radiusY;
}

string DPDrawing::Circle::getType() {
	return "Circle";
}
