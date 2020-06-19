#pragma once
#include "Command.h"
#include "../Circle.h"
#include "../Rectangle.h"
#include <SDL2/SDL.h>
#include "../SDL2_gfx_ellipse.h"
#include "strategy/Context.h"
#include "strategy/DrawCircleStrategy.h"
#include "strategy/DrawRectangleStrategy.h"
#include <memory>

using std::unique_ptr;

namespace DPDrawing {
	// Context
	class DrawShapesCommand : public Command {
		private:
		TextureManager* tm = nullptr;
		SDL_Renderer* renderer = nullptr;
		vector<unique_ptr<Shape>>* shapes;
		Context* context = nullptr;
		bool deselectAll = true;
		public:
		DrawShapesCommand(TextureManager* tm, vector<unique_ptr<Shape>>* shapes, SDL_Renderer* renderer, bool deselectAll = true) {
			this->shapes = shapes;
			this->renderer = renderer;
			this->tm = tm;
			this->deselectAll = deselectAll;
		}
		~DrawShapesCommand() {
			delete context;
		}
		void execute() {
			for(int i = shapes->size() - 1; i >= 0; i--) {
				auto& sp = shapes->at(i);
				if(deselectAll) {
					sp->Deselect();
				}
				if(sp->getType() == "Rectangle") {
					this->context = new Context(new DrawRectangleStrategy(dynamic_cast<Rectangle*>(sp.get()), renderer, tm));
				}
				else if(sp->getType() == "Circle") {
					this->context = new Context(new DrawCircleStrategy(dynamic_cast<Circle*>(sp.get()), renderer, tm));
				}
				if(context != nullptr) {
					context->executeStrategy();
					delete context;
				}
				else {
					SDL_Log("ERROR: Tried to execute strategies on NULLPTR Context in DrawShapesCommand!");
				}
			}
		}

		bool isUndoable() {
			return false;
		}
	};
}
