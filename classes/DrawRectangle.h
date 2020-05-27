#pragma once
#include "Rectangle.h"
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "Command.h"
#include <memory>
namespace DPDrawing {
	class DrawRectangle : public Command {
		public:
			DrawRectangle(Rectangle* rect, SDL_Renderer* r, TextureManager* tm) {
				mRect = rect;
				this->r = r;
				this->tm = tm;
			}
			void execute() {
				SDL_Rect* obj = mRect->getSDLObj();
				SDL_Texture* tex = (mRect->isSelected()) ? tm->getTextureByName("red") : tm->getTextureByName("white");
				SDL_RenderCopy(r, tex, NULL, obj);
				SDL_RenderPresent(r);
			}
		private:
			Rectangle* mRect;
			SDL_Renderer* r;
			TextureManager* tm;
	};
}
