#pragma once
#include "Rectangle.h"
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "DrawCommand.h"
namespace DPDrawing {
	class DrawRectangle : public DrawCommand {
		public:
			DrawRectangle(Rectangle* rect) {
				mRect = rect;
			}
			void execute(SDL_Renderer* renderer, TextureManager* tm) {
				Draw(renderer, tm, mRect->getSDLObj());
			}
		private:
			Rectangle* mRect;
			void Draw(SDL_Renderer* renderer, TextureManager* tm, SDL_Rect* obj) {
				SDL_RenderCopy(renderer, tm->getTextureByName("harald"), NULL, obj);
				SDL_RenderPresent(renderer);
			}
	};
}
