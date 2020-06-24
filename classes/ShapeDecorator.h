#include "Shape.h"
namespace DPDrawing {
	class ShapeDecorator : public Shape {
		protected:
			Shape* decoratedShape = nullptr;
		public:
		ShapeDecorator(Shape* decoratedShape) {
			this->decoratedShape = decoratedShape;
		}
		string getType() { return "ShapeDecorator"; };
    	float getArea() { return 0; };
	};
}
