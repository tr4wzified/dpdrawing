#pragma once
#include "Command.h"
#include "../Shape.h"
#include "../decorators/ShapeTextDecorator.h"
#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;

namespace DPDrawing {
	class DeleteCommand : public Command {
		private:
		vector<unique_ptr<Shape>>* shapes = nullptr;
		vector<unique_ptr<ShapeTextDecorator>>* textDecorators = nullptr;

		public:
		DeleteCommand(vector<std::unique_ptr<Shape>>* shapes, vector<std::unique_ptr<ShapeTextDecorator>>* textDecorators) {
			this->shapes = shapes;
			this->textDecorators = textDecorators;
		}

		void execute() {
			if(textDecorators == nullptr) {
				SDL_Log("ERROR: Trying to delete in DeleteCommand but textDecorators is NULLPTR!");
			}
			if(shapes == nullptr) {
				SDL_Log("ERROR: Trying to delete in DeleteCommand but shapes is NULLPTR!");
			}

			for(int i = 0; i < (int)shapes->size(); i++) {
				if (shapes->at(i)->isSelected()) {
					string deletedShapeUUID = shapes->at(i)->getUUID();
					for(int j = 0; j < (int)textDecorators->size(); j++) {
						if(deletedShapeUUID == textDecorators->at(j)->getShapeUUID()) {
							textDecorators->erase(textDecorators->begin() + j);
							j--;
						}
					}
					shapes->erase(shapes->begin() + i);
					i--;
					// Delete any text decorators that are attached to the shape
				}
			}
		}

		bool isUndoable() {
			return true;
		}
	};
}
