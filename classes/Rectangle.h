#include "Shape.h"
#include "SDL.h"
namespace DPDrawing {
	class Rectangle: public Shape {
		public:
			Rectangle(int width, int height, int posX, int posY);
			float getArea();
			void setWidth(int width);
			void setHeight(int height);
			const SDL_Rect* getSDLObj();
			SDL_Rect rect;
	};
}
