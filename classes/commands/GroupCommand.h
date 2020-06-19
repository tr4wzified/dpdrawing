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
				Composite* newComposite = nullptr;
				// If there is a selected shape
				for(unique_ptr<Shape>& s : *shapes) {
					if(s->isSelected()) {
						if(newComposite == nullptr) {
							SDL_Log("Creating new group.");
							newComposite = new Composite();
						}
						SDL_Log("Adding a shape to the composite.");
						newComposite->add(s.get());
					}
				}
				if(newComposite != nullptr) {
					// Go through each composite, if the shape is already there, delete it because it's in the new group now
					// 
					for(int i = 0; i < composite->size(); i++) {
						for(int j = 0; j < newComposite->size(); j++) {
							if(composite->at(i).getUUID() == newComposite->at(j).getUUID()) {
								composite->remove(i);
							}
						}
					}
					composite->add(newComposite);
				}
				composite->printAmountChildren();
			}
	};
}
