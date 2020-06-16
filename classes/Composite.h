#pragma once
#include "Component.h"
#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <SDL2/SDL.h>
using std::vector;
namespace DPDrawing {
	class Composite : public Component {
		private:
			vector<Component*> children;
			std::string UUID;
		public:
			Composite() {
				// Credit to twocrush
				// https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library
				static std::random_device rd;
				static std::mt19937 gen(rd());
				static std::uniform_int_distribution<> dis(0, 15);
				static std::uniform_int_distribution<> dis2(8, 11);
				std::stringstream ss;
				int i;
				ss << std::hex;
				for (i = 0; i < 8; i++) {
				    ss << dis(gen);
				}
				ss << "-";
				for (i = 0; i < 4; i++) {
				    ss << dis(gen);
				}
				ss << "-4";
				for (i = 0; i < 3; i++) {
				    ss << dis(gen);
				}
				ss << "-";
				ss << dis2(gen);
				for (i = 0; i < 3; i++) {
				    ss << dis(gen);
				}
				ss << "-";
				for (i = 0; i < 12; i++) {
				    ss << dis(gen);
				};
				this->UUID = ss.str();
			}
			~Composite() {
				for (unsigned int i = 0; i < children.size(); i++ ) {
				  delete children.at(i);
				}
			}
			Component* getChild(const unsigned int index) {
				return children.at(index);
			}

			void add(Component* component) {
				children.push_back(component);
			}

			void remove(const unsigned int index) {
				Component* child = children.at(index);
				children.erase(children.begin() + index);
				delete child;
			}

			void operation() {
				for(Component* c : children) {
					c->operation();
				}
			}
			virtual string getUUID() {
				return UUID;
			}

			virtual void printAmountChildren() {
				SDL_Log("%d", (int)children.size());
			}
	};
}
