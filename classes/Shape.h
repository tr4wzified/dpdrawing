#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "Selectable.h"

using std::string;
namespace DPDrawing {
class Shape: public Selectable {
public:
    virtual void setPosX(int posX);
    virtual void setPosY(int posY);
    virtual void setWidth(int width);
    virtual void setHeight(int height);
	virtual int getPosX();
	virtual int getPosY();
	virtual int getWidth();
	virtual int getHeight();
	virtual string getType() = 0;
    virtual float getArea() = 0;

private:
	int posX;
	int posY;
	int width;
	int height;
};
}
