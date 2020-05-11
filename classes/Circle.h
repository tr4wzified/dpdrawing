#pragma once
#include <SDL2/SDL.h>
#include "Shape.h"
namespace DPDrawing {
	class Circle: public Shape {
		public:
			Circle(int width, int height, int posX, int posY);
			float getArea();
			void setWidth(int width);
			void setHeight(int height);
			int getRadiusX();
			int getRadiusY();
			void setRadiusX(int radiusX);
			void setRadiusY(int radiusY);

		private:
			int radiusX;
			int radiusY;

	};
}
