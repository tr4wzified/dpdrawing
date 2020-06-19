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
			void RecursiveDelete(Component* c, Component* toCheckAgainst) {
				// For each component in composite c, check if it is the component toCheckAgainst
				SDL_Log("RecursiveDelete() called! Component c size: %d, Component toCheckAgainst size: %d", c->size(), toCheckAgainst->size());
				for(int j = 0; j < toCheckAgainst->size(); j++) {
					SDL_Log("toCheckAgainst j: %d", j);
					if(toCheckAgainst->getChild(j)->size() == 0) {
						SDL_Log("That j is a leaf!");
						for(int i = 0; i < c->size(); i++) {
							SDL_Log("c i: %d", i);
							if(c->getChild(i) == nullptr) {
								SDL_Log("ERROR: getChild(i) is a NULLPTR!");
							}
							// if it's a leaf (shape)
							if(c->getChild(i)->size() == 0) {
								SDL_Log("that i is a leaf!");
								// Identical component found!
								if(c->getChild(i)->getUUID() == toCheckAgainst->getChild(j)->getUUID()) {
									SDL_Log("they are the same! removing");
									c->remove(i);
								}
							}
							else {
								SDL_Log("hit else");
								// Recursive
								RecursiveDelete(c->getChild(i), toCheckAgainst);
							}
						}
					}
				}
			}
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
					RecursiveDelete(composite, newComposite);
					composite->add(newComposite);
				}
				//composite->print();
			}
	};
}
