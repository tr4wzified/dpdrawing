#pragma once
#include <SDL2/SDL.h>
#include "Shape.h"
namespace DPDrawing {
	class Circle: public Shape {
		public:
			Circle(int width, int height, int posX, int posY);
			float getArea();
	};
}
