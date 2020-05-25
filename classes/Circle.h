#pragma once
#include <SDL2/SDL.h>
#include "Shape.h"
namespace DPDrawing {
	class Circle: public Shape {
		public:
			Circle(int width, int height, int posX, int posY);
			float getArea();
			void setRealPosX(int posX);
			void setRealPosY(int posY);
			void setPosX(int posX);
			void setPosY(int posY);
			void setWidth(int width);
			void setHeight(int height);
			void setRadiusX(int radiusX);
			void setRadiusY(int radiusY);
			void setCenterX(int centerY);
			void setCenterY(int centerY);
			int getPosX();
			int getPosY();
			int getWidth();
			int getHeight();
			int getCenterX();
			int getCenterY();
			int getRadiusX();
			int getRadiusY();
			string getType();
			bool getSelected();
			void Select();
			void Deselect();

		private:
			int posX;
			int posY;
			int width;
			int height;
			int radiusX;
			int radiusY;
			bool isSelected = false;
			int amountDynamicResized = 0;

	};
}
