#include "Rectangle.h"
DPDrawing::Rectangle::Rectangle(int width, int height, int posX, int posY) {
	Rectangle::setWidth(width);
	Rectangle::setHeight(height);
	Rectangle::setPosX(posX);
	Rectangle::setPosY(posY);
}

float DPDrawing::Rectangle::getArea() {
    return this->width * this->height;
}

void DPDrawing::Rectangle::setPosX(int posX) {
    this->posX = posX;
    rect.x = posX;
}

void DPDrawing::Rectangle::setPosY(int posY) {
    this->posY = posY;
    rect.y = posY;
}
void DPDrawing::Rectangle::setWidth(int width) {
    this->width = width;
    rect.w = width;
}

void DPDrawing::Rectangle::setHeight(int height) {
    this->height = height;
    rect.h = height;
}

int DPDrawing::Rectangle::getPosX() {
	return this->posX;
}

int DPDrawing::Rectangle::getPosY() {
	return this->posY;
}

int DPDrawing::Rectangle::getWidth() {
	return this->width;
}

int DPDrawing::Rectangle::getHeight() {
	return this->height;
}

string DPDrawing::Rectangle::getType() {
	return "Rectangle";
}

bool DPDrawing::Rectangle::getSelected() {
	return isSelected;
}

void DPDrawing::Rectangle::Select() {
	isSelected = true;
}

void DPDrawing::Rectangle::Deselect() {
	isSelected = false;
}

void DPDrawing::Rectangle::setRect(int mouseX, int mouseY, int mouseEndX, int mouseEndY) {
    if (mouseEndX > mouseX && mouseEndY > mouseY) {
	setPosX(mouseX);
	setPosY(mouseY);
    } else if (mouseEndX > mouseX && mouseEndY < mouseY) {
	setPosX(mouseX);
	setPosY(mouseEndY);
    } else if (mouseEndX < mouseX && mouseEndY < mouseY) {
	setPosX(mouseEndX);
	setPosY(mouseEndY);
    } else {
	setPosX(mouseEndX);
	setPosY(mouseY);
    }
    setWidth(abs(mouseEndX - mouseX));
    setHeight(abs(mouseEndY - mouseY));
}

SDL_Rect* DPDrawing::Rectangle::getSDLObj() {
    return &this->rect;
}
