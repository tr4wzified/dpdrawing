#pragma once
#include <SDL2/SDL.h>
#include "TextureManager.h"
namespace DPDrawing {
	class DrawCommand {
		public:
		virtual void execute(SDL_Renderer* renderer, TextureManager* tm, int mouseX, int mouseY, int mouseEndX, int mouseEndY, bool mouseBeingHeld) = 0;
	};
}
