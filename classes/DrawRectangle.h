#pragma once
#include "Rectangle.h"
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "DrawCommand.h"
namespace DPDrawing {
	class DrawRectangle : public DrawCommand {
		public:
			DrawRectangle(Rectangle* rect) {
				SDL_Log("Initializing DrawRectangle");
				mRect = rect;
			}
			void execute(SDL_Renderer* renderer, TextureManager* tm) {
				SDL_Log("Creating tempRect");
				SDL_Rect* tempRect = mRect->getSDLObj();
				SDL_Log("Executing DrawRectangle.Draw()");
				Draw(renderer, tm, tempRect);
			}
		private:
			Rectangle* mRect;
			void Draw(SDL_Renderer* renderer, TextureManager* tm, SDL_Rect* obj) {
				SDL_Log("Getting harald texture");
				SDL_Texture* tempTex = tm->getTextureById(0);
				SDL_Log("Applying TextureManager texture to Rectangle");
				SDL_RenderCopy(renderer, tempTex, NULL, obj);
			}
	};
}
