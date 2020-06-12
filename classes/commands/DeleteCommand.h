#pragma once
#include "Command.h"
#include "../Shape.h"
#include <vector>
#include <memory>
using std::vector;

namespace DPDrawing {
	class DeleteCommand : public Command {
		private:
		vector<std::unique_ptr<Shape>>* shapes = nullptr;

		public:
		DeleteCommand(vector<std::unique_ptr<Shape>>* shapes) {
			this->shapes = shapes;
		}

		void execute() {
			for(int i = 0; i < (int)shapes->size(); i++) {
				if (shapes->at(i)->isSelected()) {
					shapes->erase(shapes->begin() + i);
					break;
				}
			}
		}

		bool isUndoable() {
			return true;
		}
	};
}
