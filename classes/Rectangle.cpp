#include "Rectangle.h"
DPDrawing::Rectangle::Rectangle(int width, int height, int posX, int posY) {
    this->width = width;
    this->height = height;
    this->posX = posX;
    this->posY = posY;
    this->rect = { this->width, this->height, this->posX, this->posY };
}

void DPDrawing::Rectangle::setWidth(int width) {
    this->width = width;
    rect.w = width;
}

void DPDrawing::Rectangle::setHeight(int height) {
    this->height = height;
    rect.h = height;
}

void DPDrawing::Rectangle::setPosX(int posX) {
    this->posX = posX;
    rect.x = posX;
}

void DPDrawing::Rectangle::setPosY(int posY) {
    this->posY = posY;
    rect.y = posY;
}

float DPDrawing::Rectangle::getArea() {
    return this->width * this->height;
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
