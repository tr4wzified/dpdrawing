#pragma once
#include "../Rectangle.h"
#include "../Invoker.h"
#include "../TextureManager.h"
#include "../MouseHandler.h"
#include "strategy/Context.h"
#include "strategy/DrawRectangleStrategy.h"
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
using std::vector;
using std::unique_ptr;
namespace DPDrawing {
	class CreateRectangleCommand : public Command {
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
			CreateRectangleCommand(Invoker* inv, vector<unique_ptr<Shape>>* shapes, MouseHandler* mh, SDL_Renderer* renderer, TextureManager* tm, bool useDynamicResize) {
				this->inv = inv;
				this->shapes = shapes;
				this->mh = mh;
				this->renderer = renderer;
				this->tm = tm;
				this->useDynamicResize = useDynamicResize;
			}
		void execute() {
			Rectangle* rec = new Rectangle(mh->getMouseEndX() - mh->getMouseX(), mh->getMouseEndY() - mh->getMouseY(), mh->getMouseX(), mh->getMouseY());
			if(useDynamicResize) {
				dynamicResize(rec);
			}
			shapes->push_back(std::make_unique<Rectangle>(*rec));
			Context* context = new Context(new DrawRectangleStrategy(rec, renderer, tm));
			context->executeStrategy();
			delete context;
		}
		bool isUndoable() {
			return true;
		}
	};
}
