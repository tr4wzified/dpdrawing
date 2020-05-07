#pragma once
#include <SDL2/SDL.h>
#include "TextureManager.h"
namespace DPDrawing {
	class DrawCommand {
		public:
		virtual void execute(SDL_Renderer* renderer, TextureManager* tm) = 0;
	};
}
