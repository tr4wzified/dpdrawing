#pragma once
#include <SDL2/SDL.h>
namespace DPDrawing {
class Shape {
public:
    float getArea();
	/* int getId() { */
	/* 	return getHeight() * 7 + getWidth() * 7 + getPosX() * 7 + getPosY() * 7; */
	/* } */
    void setWidth(int width);
    void setHeight(int height);
	int getWidth();
	int getHeight();
	int getPosX();
	int getPosY();
    void setPosX(int posX);
    void setPosY(int posY);
    int width;
    int height;
    int posX;
    int posY;
	bool isSelected = false;
};
}
