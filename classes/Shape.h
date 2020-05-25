#pragma once
#include <SDL2/SDL.h>
#include <string>

#include "Selectable.h"

using std::string;
namespace DPDrawing {
class Shape: public Selectable {
public:
    virtual float getArea() = 0;
    virtual void setPosX(int posX) = 0;
    virtual void setPosY(int posY) = 0;
    virtual void setWidth(int width) = 0;
    virtual void setHeight(int height) = 0;
	virtual int getPosX() = 0;
	virtual int getPosY() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual string getType() = 0;
};
}
