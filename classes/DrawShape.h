#pragma once
#include "Rectangle.h"
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "Rectangle.h"
#include "Circle.h"
#include "DrawCommand.h"
#include "DrawRectangle.h"
#include "DrawCircle.h"
#include <memory>
namespace DPDrawing {
	class DrawShape : public DrawCommand {
		public:
		DrawShape(Shape* shape) {
			this->shape = shape;
		}
		void execute() {
			if(shape != nullptr) {
				string type = shape->getType();
				if(type == "Rectangle") {
					Rectangle r(shape->getWidth(),shape->getHeight(),shape->getPosX(),shape->getPosY());
					DrawRectangle* dr = new DrawRectangle(&r);
				}
				else if(type == "Circle") {
					Circle c(shape->getWidth(), shape->getHeight(), (shape->getPosX() + (shape->getWidth() / 2)),(shape->getPosY() + (shape->getHeight() / 2)));
				}
			}
			else {
				SDL_Log("ERROR: Cannot execute a DrawShape with no Shape!");
			}
		}
		private:
		Shape* shape;

	};
}
