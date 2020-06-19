#include "Circle.h"
DPDrawing::Circle::Circle(int width, int height, int posX, int posY) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> dis(0, 15);
	static std::uniform_int_distribution<> dis2(8, 11);
	std::stringstream ss;
	int i;
	ss << std::hex;
	for (i = 0; i < 8; i++) {
	    ss << dis(gen);
	}
	ss << "-";
	for (i = 0; i < 4; i++) {
	    ss << dis(gen);
	}
	ss << "-4";
	for (i = 0; i < 3; i++) {
	    ss << dis(gen);
	}
	ss << "-";
	ss << dis2(gen);
	for (i = 0; i < 3; i++) {
	    ss << dis(gen);
	}
	ss << "-";
	for (i = 0; i < 12; i++) {
	    ss << dis(gen);
	};
	this->setUUID(ss.str());
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

void DPDrawing::Circle::print() {
	SDL_Log("Circle");
}
