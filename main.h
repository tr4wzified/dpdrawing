#pragma once
#include<stdlib.h>
#include<string>
#include "SDL.h"
#include "classes/Rectangle.h"
#include "classes/Circle.h"
namespace DPDrawing {
	class Main {
		public:
			int Init(const int SCREEN_WIDTH = 1280, const int SCREEN_HEIGHT = 720);
			void Update(SDL_Window*& window, SDL_Renderer*& renderer);
			int Quit();
			int main(int argc, char* argv[]);
	};
}
