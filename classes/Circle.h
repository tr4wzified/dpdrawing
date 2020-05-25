#pragma once
#include <SDL2/SDL.h>
#include "Shape.h"
namespace DPDrawing {
	class Circle: public Shape {
		public:
			Circle(int width, int height, int posX, int posY);
			float getArea();
			void setCenterX(int centerY);
			void setCenterY(int centerY);
			int getCenterX();
			int getCenterY();
			int getRadiusX();
			int getRadiusY();
			string getType();

	};
}
