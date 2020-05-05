#pragma once
#include <SDL2/SDL.h>
#include "Shape_old.h"
namespace DPDrawing {
	class Circle: public Shape_old {
		public:
			Circle(int width, int height, int posX, int posY);
			float getArea();
	};
}
