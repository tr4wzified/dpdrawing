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
					if(toCheckAgainst->size() != 0) {
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
									SDL_Log("c->getChild(%d)->getUUID() = %s", i, c->getChild(i)->getUUID().c_str());
									SDL_Log("toCheckAgainst->getChild(%d)->getUUID() = %s", j, toCheckAgainst->getChild(j)->getUUID().c_str());
									// Identical component found!
									if(c->getChild(i)->getUUID() == toCheckAgainst->getChild(j)->getUUID()) {
										SDL_Log("they are the same! removing");
										c->remove(i);
										i--;
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
			}

			void deleteRecursive(Component* c, Component* removeAllChildrenFromC) {
				if(c->size() != 0) {
					if(removeAllChildrenFromC->size() != 0) {
						for(int i = 0; i < c->size(); i++) {
							if(c->getChild(i)->size() == 0) {
								for(int j = 0; j < removeAllChildrenFromC->size(); j++) {
									if(c->getChild(i)->getUUID() == removeAllChildrenFromC->getChild(j)->getUUID()) {
										c->remove(i);
										//i--;
									}
								}
							}
							// Pure virtual bug?
							/*
							else {
								deleteRecursive(c->getChild(i), removeAllChildrenFromC);
							}
							*/
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
					deleteRecursive(composite, newComposite);
					composite->add(newComposite);
				}
				//composite->print();
			}
	};
}
