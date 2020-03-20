#pragma once
#include "Shape.h"
namespace DPDrawing {
	class Rectangle: public Shape {
		public:
			Rectangle(int width, int height, int posX, int posY);
			float getArea();
			const SDL_Rect* getSDLObj();
		private:
			SDL_Rect rect;
	};
}
