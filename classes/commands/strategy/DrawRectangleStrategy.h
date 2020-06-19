#pragma once
#include "../../Rectangle.h"
#include <SDL2/SDL.h>
#include "../../SDL2_gfx_ellipse.h"
#include "../../TextureManager.h"
#include "Strategy.h"
namespace DPDrawing {
	class DrawRectangleStrategy : public Strategy {
		public:
			DrawRectangleStrategy(Rectangle* rect, SDL_Renderer* r, TextureManager* tm) {
				mRect = rect;
				this->r = r;
				this->tm = tm;
			}
			
			void execute() {
				if(mRect == nullptr) {
					SDL_Log("ERROR: mRect is a NULLPTR in DrawRectangleStrategy!");
				}
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
