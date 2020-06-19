#pragma once
#include "../Rectangle.h"
#include "../Invoker.h"
#include "../TextureManager.h"
#include "../MouseHandler.h"
#include "../Composite.h"
#include "strategy/Context.h"
#include "strategy/DrawCircleStrategy.h"
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
			Composite* composite = nullptr;
			bool useDynamicResize = false;
			void dynamicResize(Shape* mShape) {
				mShape->setPosX(std::min(mh->getMouseX(), mh->getMouseEndX()));
				mShape->setPosY(std::min(mh->getMouseY(), mh->getMouseEndY()));
				mShape->setWidth(abs(mh->getMouseEndX() - mh->getMouseX()));
				mShape->setHeight(abs(mh->getMouseEndY() - mh->getMouseY()));
			}
			public:
			CreateCircleCommand(Invoker* inv, vector<unique_ptr<Shape>>* shapes, MouseHandler* mh, SDL_Renderer* renderer, TextureManager* tm, Composite* composite, bool useDynamicResize) {
				this->inv = inv;
				this->shapes = shapes;
				this->mh = mh;
				this->renderer = renderer;
				this->tm = tm;
				this->composite = composite;
				this->useDynamicResize = useDynamicResize;
			}
		void execute() {
			Circle* circ = new Circle(mh->getMouseEndX() - mh->getMouseX(), mh->getMouseEndY() - mh->getMouseY(), mh->getMouseX(), mh->getMouseY());
			if(useDynamicResize) {
				dynamicResize(circ);
			}
			shapes->push_back(std::make_unique<Circle>(*circ));
			composite->add(circ);
			Context* context = new Context(new DrawCircleStrategy(circ, renderer, tm));
			context->executeStrategy();
			delete context;
		}
		bool isUndoable() {
			return true;
		}
	};
}

