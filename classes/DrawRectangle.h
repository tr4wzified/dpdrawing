#pragma once
#include "Rectangle.h"
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "DrawCommand.h"
#include <memory>
namespace DPDrawing {
	class DrawRectangle : public DrawCommand {
		public:
			DrawRectangle(Rectangle* rect) {
				mRect = rect;
			}
			void execute(SDL_Renderer* renderer, TextureManager* tm) {
				Draw(renderer, tm);
			}
		private:
			Rectangle* mRect;
			void Draw(SDL_Renderer* renderer, TextureManager* tm) {
				SDL_Rect* obj = mRect->getSDLObj();
				SDL_Texture* tempTex = nullptr;
				if(!mRect->isSelected()) {
					tempTex = tm->getTextureByName("white");
				}
				else {
					tempTex = tm->getTextureByName("red");
				}
				SDL_RenderCopy(renderer, tempTex, NULL, obj);
			}

	};
}
