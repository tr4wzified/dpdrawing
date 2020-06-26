#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Selectable.h"
#include "Component.h"

using std::string;
namespace DPDrawing {
class Shape: public Selectable, public Component {
public:
	~Shape() {}
    virtual void setPosX(int posX);
    virtual void setPosY(int posY);
    virtual void setWidth(int width);
    virtual void setHeight(int height);
	virtual int getPosX();
	virtual int getPosY();
	virtual int getWidth();
	virtual int getHeight();
	virtual string getType() = 0;
    virtual float getArea() { return 0; };
	virtual string getUUID() {
		return UUID;
	}
	virtual void setUUID(std::string UUID) {
		this->UUID = UUID;
	}

	int size() {
		return 0;
	}

	void remove(int) {}

	void print() {
		SDL_Log("Shape");
	}

	virtual void operation() {
		std::cout << "test";
	}

private:
	int posX;
	int posY;
	int width;
	int height;
	string UUID;

};
}
