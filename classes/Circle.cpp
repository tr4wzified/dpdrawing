#include "Circle.h"
DPDrawing::Circle::Circle(int width, int height, int posX, int posY) {
	this->setWidth(width);
	this->setHeight(height);
	this->setPosX(posX);
	this->setPosY(posY);
}

float DPDrawing::Circle::getArea() {
	return M_PI * (Shape::getWidth() / 2) * (Shape::getHeight() / 2);
}

void DPDrawing::Circle::setCenterX(int centerX) {
	Shape::setPosX(centerX - (Shape::getWidth() / 2));
}

void DPDrawing::Circle::setCenterY(int centerY) {
	Shape::setPosY(centerY - (Shape::getHeight() / 2));
}

string DPDrawing::Circle::getType() {
	return "Circle";
}
