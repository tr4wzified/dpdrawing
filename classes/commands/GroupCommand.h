#pragma once
#include "Command.h"
#include "../Shape.h"
#include "../Component.h"
#include "../Composite.h"
#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;

namespace DPDrawing {
	class GroupCommand : public Command {
		private: 
			vector<unique_ptr<Shape>>* shapes = nullptr;
			Composite* composite = nullptr;
		public:
			GroupCommand(Composite* composite, vector<unique_ptr<Shape>>* shapes) {
				this->composite = composite;
				this->shapes = shapes;
			}
			bool isUndoable() {
				return false;
			}
			void execute() {
				for(unique_ptr<Shape>& s : *shapes) {
					if(s->isSelected()) {
						SDL_Log("Adding a shape to the composite.");
						composite->add(s.get());
					}
				}
				composite->printAmountChildren();
			}
	};
}
