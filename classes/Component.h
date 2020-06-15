#pragma once
namespace DPDrawing {
	class Component {
		public:
			virtual ~Component() {}
			virtual Component* getChild(int) { return 0; }
			virtual void add(Component*) {}
			virtual void remove(int) { }
			virtual void operation() = 0;
	};	
}
