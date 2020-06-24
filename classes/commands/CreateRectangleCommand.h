#pragma once
#include "../Rectangle.h"
#include "../Invoker.h"
#include "../TextureManager.h"
#include "../MouseHandler.h"
#include "../Composite.h"
#include "strategy/Context.h"
#include "strategy/DrawRectangleStrategy.h"
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "../decorators/ShapeDecorator.h"
#include "../decorators/TextTopDecorator.h"
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
			Composite* composite = nullptr;
			bool useDynamicResize = false;
			void dynamicResize(Shape* mShape) {
				mShape->setPosX(std::min(mh->getMouseX(), mh->getMouseEndX()));
				mShape->setPosY(std::min(mh->getMouseY(), mh->getMouseEndY()));
				mShape->setWidth(abs(mh->getMouseEndX() - mh->getMouseX()));
				mShape->setHeight(abs(mh->getMouseEndY() - mh->getMouseY()));
			}
			public:
			CreateRectangleCommand(Invoker* inv, vector<unique_ptr<Shape>>* shapes, MouseHandler* mh, SDL_Renderer* renderer, TextureManager* tm, Composite* composite, bool useDynamicResize) {
				this->inv = inv;
				this->shapes = shapes;
				this->mh = mh;
				this->renderer = renderer;
				this->tm = tm;
				this->composite = composite;
				this->useDynamicResize = useDynamicResize;
			}
		void execute() {
			Rectangle* rec = new Rectangle(mh->getMouseEndX() - mh->getMouseX(), mh->getMouseEndY() - mh->getMouseY(), mh->getMouseX(), mh->getMouseY());
			if(useDynamicResize) {
				dynamicResize(rec);
			}
			shapes->push_back(std::make_unique<Rectangle>(*rec));
			composite->add(rec);
			Context* context = new Context(new DrawRectangleStrategy(rec, renderer, tm));
			context->executeStrategy();
			delete context;
			Shape* s = rec;
			SDL_Log("Shape: %s", s->getType().c_str());
			ShapeDecorator* sd = new ShapeDecorator(s, tm, shapes, renderer, inv);
			SDL_Log("ShapeDecorator: %s", sd->getType().c_str());
			TextTopDecorator* ttd = new TextTopDecorator(s, tm, shapes, renderer, inv);
			SDL_Log("TextTopDecorator: %s", ttd->getType().c_str());
			delete sd;
			delete ttd;
		}
		bool isUndoable() {
			return true;
		}
	};
}
