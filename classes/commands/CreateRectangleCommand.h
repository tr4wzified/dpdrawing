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

#include "../decorators/ShapeTextDecorator.h"
#include "../decorators/ShapeTextTopDecorator.h"
#include "../decorators/ShapeTextBottomDecorator.h"
#include "../decorators/ShapeTextLeftDecorator.h"
#include "../decorators/ShapeTextRightDecorator.h"
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
			ShapeTextDecorator* sd = new ShapeTextDecorator(s, tm, shapes, renderer, inv);
			//SDL_Log("ShapeTextDecorator: %s", sd->getType().c_str());
			string test;
			SDL_Log("Please input your text to display in the middle below!");
			std::cin >> test;
			sd->drawText(test);
			ShapeTextTopDecorator* ttd = new ShapeTextTopDecorator(s, tm, shapes, renderer, inv);
			//SDL_Log("ShapeTextTopDecorator: %s", ttd->getType().c_str());
			ttd->drawText("top text");
			ShapeTextBottomDecorator* ttb = new ShapeTextBottomDecorator(s, tm, shapes, renderer, inv);
			ttb->drawText("bottom text");
			ShapeTextLeftDecorator* ttl = new ShapeTextLeftDecorator(s, tm, shapes, renderer, inv);
			ttl->drawText("left text");
			ShapeTextRightDecorator* ttr = new ShapeTextRightDecorator(s, tm, shapes, renderer, inv);
			ttr->drawText("right text");
			delete sd;
			delete ttd;
			delete ttb;
		}
		bool isUndoable() {
			return true;
		}
	};
}
