#include "Circle.h"
DPDrawing::Circle::Circle(int width, int height, int posX, int posY) {
	this->setWidth(width);
	this->setHeight(height);
	this->setPosX(posX);
	this->setPosY(posY);
}

float DPDrawing::Circle::getArea() {
	return M_PI * (this->getWidth() / 2) * (this->getHeight() / 2);
}

void DPDrawing::Circle::setCenterX(int centerX) {
	this->setPosX(centerX - (this->getWidth() / 2));
}

void DPDrawing::Circle::setCenterY(int centerY) {
	this->setPosY(centerY - (this->getHeight() / 2));
}

string DPDrawing::Circle::getType() {
	return "Circle";
}
