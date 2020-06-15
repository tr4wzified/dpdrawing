#pragma once
#include "../Selectable.h"
#include "../Shape.h"
#include "../Circle.h"
#include "../Rectangle.h"
#include <SDL2/SDL.h>
#include "../SDL2_gfx_ellipse.h"
#include "../Invoker.h"
#include "DrawRectangleCommand.h"
#include "DrawCircleCommand.h"
#include "Command.h"
#include <memory>

using std::unique_ptr;

namespace DPDrawing {
	class DrawShapesCommand : public Command {
		private:
		Invoker* inv = nullptr;
		TextureManager* tm = nullptr;
		SDL_Renderer* renderer = nullptr;
		vector<unique_ptr<Shape>>* shapes;
		DrawRectangleCommand* drawrec = nullptr;
		DrawCircleCommand* drawcirc = nullptr;
		bool deselectAll = true;
		public:
		DrawShapesCommand(Invoker* inv, TextureManager* tm, vector<unique_ptr<Shape>>* shapes, SDL_Renderer* renderer, bool deselectAll = true) {
			this->inv = inv;
			this->shapes = shapes;
			this->renderer = renderer;
			this->tm = tm;
			this->deselectAll = deselectAll;
		}
		~DrawShapesCommand() {
			delete drawrec;
			delete drawcirc;
		}
		void execute() {
			for(int i = shapes->size() - 1; i >= 0; i--) {
				auto& sp = shapes->at(i);
				if(deselectAll) {
					sp->Deselect();
				}
				if(sp->getType() == "Rectangle") {
					drawrec = new DrawRectangleCommand(dynamic_cast<Rectangle*>(sp.get()), renderer, tm);
					inv->addCommand(drawrec);
				}
				else if(sp->getType() == "Circle") {
					drawcirc = new DrawCircleCommand(dynamic_cast<Circle*>(sp.get()), renderer, tm);
					inv->addCommand(drawcirc);
				}
			}
		}

		bool isUndoable() {
			return false;
		}
			
	};
}
