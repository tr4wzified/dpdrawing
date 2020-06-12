#pragma once
#include "../Rectangle.h"
#include "../Invoker.h"
#include "../TextureManager.h"
#include "../MouseHandler.h"
#include "DrawCircleCommand.h"
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
using std::vector;
using std::unique_ptr;
namespace DPDrawing {
	class CreateCircleCommand : public Command {
		private:
			Invoker* inv = nullptr;
			vector<unique_ptr<Shape>>* shapes = nullptr;
			MouseHandler* mh = nullptr;
			SDL_Renderer* renderer = nullptr;
			TextureManager* tm = nullptr;
			bool useDynamicResize = false;
			void dynamicResize(Shape* mShape) {
				mShape->setPosX(std::min(mh->getMouseX(), mh->getMouseEndX()));
				mShape->setPosY(std::min(mh->getMouseY(), mh->getMouseEndY()));
				mShape->setWidth(abs(mh->getMouseEndX() - mh->getMouseX()));
				mShape->setHeight(abs(mh->getMouseEndY() - mh->getMouseY()));
			}
			public:
			CreateCircleCommand(Invoker* inv, vector<unique_ptr<Shape>>* shapes, MouseHandler* mh, SDL_Renderer* renderer, TextureManager* tm, bool useDynamicResize) {
				this->inv = inv;
				this->shapes = shapes;
				this->mh = mh;
				this->renderer = renderer;
				this->tm = tm;
				this->useDynamicResize = useDynamicResize;
			}
		void execute() {
			Circle* circ = new Circle(mh->getMouseEndX() - mh->getMouseX(), mh->getMouseEndY() - mh->getMouseY(), mh->getMouseX(), mh->getMouseY());
			if(useDynamicResize) {
				dynamicResize(circ);
			}
			shapes->push_back(std::make_unique<Circle>(*circ));
			DrawCircleCommand* drawcirc = new DrawCircleCommand(circ, renderer, tm);
			inv->addCommand(drawcirc);
		}
		bool isUndoable() {
			return true;
		}
	};
}

