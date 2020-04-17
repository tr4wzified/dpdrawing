#pragma once
#include <SDL2/SDL.h>
namespace DPDrawing {
	class Pixel {
		public:
			Pixel(int posX, int posY, int r, int g, int b, int a);
			int color[4] = {0};
			int posX;
			int posY;
			//Pixel(int posX, int posY, int color[4]);
			int Draw(SDL_Renderer*& renderer);
	};
}
