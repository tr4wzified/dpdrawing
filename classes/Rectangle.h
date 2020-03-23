#include "Shape.h"
#include "SDL.h"
namespace DPDrawing {
	class Rectangle: public Shape {
		public:
			Rectangle(int width, int height, int posX, int posY);
			float getArea();
			void setWidth(int width);
			void setHeight(int height);
			void setPosX(int posX);
			void setPosY(int posY);
			const SDL_Rect* getSDLObj();
			void setRect(int mouseX, int mouseY, int mouseEndX, int mouseEndY);
			SDL_Rect rect;
	};
}
