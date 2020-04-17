
/* CPP
drawRectangle(width, height,posX,posY) {
		    this->width = width;
		    this->height = height;
		    this->posX = posX;
		    this->posY = posY;
		    this->rect = {this->width, this->height, this->posX, this->posY};
	    }

	    void DPDrawing::DrawRectangle::setWidth(int width) {
	    	this->width = width;
	    	rect.w = width;
	    }

	    void DPDrawing::DrawRectangle::setHeight(int height) {
	    	this->height = height;
	    	rect.h = height;
	    }

	    void DPDrawing::DrawRectangle::setPosX(int posX) {
	    	this->posX = posX;
	    	rect.x = posX;
	    }

	    void DPDrawing::DrawRectangle::setPosY(int posY) {
	    	this->posY = posY;
	    	rect.y = posY;
	    }

	    float DPDrawing::DrawRectangle::getArea() {
	    	return this->width * this->height;
	    }

	    void DPDrawing::DrawRectangle::setRect(int mouseX, int mouseY, int mouseEndX, int mouseEndY) {
	    	if (mouseEndX > mouseX && mouseEndY > mouseY) {
		    	posX = mouseX;
		    	posY = mouseY;
		    }
		    else if (mouseEndX < mouseEndX && mouseEndY > mouseY) {
		    	posX = mouseEndX;
		    	posY = mouseY;
		    }
		    else if (mouseEndX > mouseX && mouseEndY < mouseY) {
		    	posX = mouseX;
		    	posY = mouseEndY;
		    }
		    else if(mouseEndX < mouseX && mouseEndY < mouseY) {
		    	posX = mouseEndX;
		    	posY = mouseEndY;
		    }
		    else {
		    	posX = mouseEndX;
		    	posY = mouseY;
		    }
		    width = abs(mouseEndX - mouseX);
		    height = abs(mouseEndY - mouseY);
		    rect = {posX, posY, width, height};
	    }
        
	    const SDL_Rect* DPDrawing::DrawRectangle::getSDLObj() {
		    return &this->rect;
	    }

Header

#pragma once
#include "SDL.h"
#include "Shape.h"

namespace DPDrawing {
	class DrawRectangle: public Shape {
		public:
			DrawRectangle(int width, int height, int posX, int posY);
			float getArea();
			void setWidth(int width);
			void setHeight(int height);
			void setPosX(int posX);
			void setPosY(int posY);
			const SDL_Rect* getSDLObj();
			void setRect(int mouseX, int mouseY, int mouseEndX, int mouseEndY);
			SDL_Rect rect;
	};
}

*/