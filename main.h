#pragma once
#include<stdlib.h>
#include<string>
#include<vector>
#include <SDL2/SDL.h>
#include "classes/Rectangle.h"
#include "classes/Circle.h"
#include "classes/Pixel.h"
#include "commandpattern/Shape.h"
#include "commandpattern/DrawRectangle.h"
#include "commandpattern/DrawCircle.h"
#include "commandpattern/Drawer.h"

namespace DPDrawing {
	class Main {
		public:
			
			
			int Quit();
			int Init(const int SCREEN_WIDTH = 1280, const int SCREEN_HEIGHT = 720);
			void Update(SDL_Window*& window, SDL_Renderer*& gRenderer);
			int main(int argc, char* argv[]);
	};
}
