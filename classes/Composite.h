#pragma once
#include "Component.h"
#include <vector>
using std::vector;
namespace DPDrawing {
	class Composite : public Component {
		private:
			vector<Component*> children;
		public:
			~Composite() {
				for ( unsigned int i = 0; i < children.size(); i++ ) {
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
	};
}
