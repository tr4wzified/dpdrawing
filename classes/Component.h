#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <random>
#include <sstream>
using std::string;
namespace DPDrawing {
	class Component {
		public:
			virtual ~Component() {}
			virtual Component* getChild(int) { return 0; }
			virtual void add(Component*) {}
			virtual void remove(int) = 0;
			virtual void operation() = 0;
			virtual string getUUID() = 0;
			virtual int size() = 0;
			virtual void print() = 0;
	};	
}
