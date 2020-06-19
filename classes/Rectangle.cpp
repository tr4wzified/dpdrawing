#include "Rectangle.h"
DPDrawing::Rectangle::Rectangle(int width, int height, int posX, int posY) {
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

void DPDrawing::Rectangle::print() {
	SDL_Log("Rectangle");
}
