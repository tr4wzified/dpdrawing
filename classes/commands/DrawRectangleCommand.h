#pragma once
#include "../Rectangle.h"
#include <SDL2/SDL.h>
#include "../TextureManager.h"
#include "Command.h"
#include <memory>
namespace DPDrawing {
	class DrawRectangleCommand : public Command {
		public:
			DrawRectangleCommand(Rectangle* rect, SDL_Renderer* r, TextureManager* tm) {
				mRect = rect;
				this->r = r;
				this->tm = tm;
			}
			
			void execute() {
				if(mRect == nullptr) {
					SDL_Log("ERROR: mRect is a NULLPTR in DrawRectangleCommand!");
				}
				SDL_Rect* obj = mRect->getSDLObj();
				SDL_Texture* tex = (mRect->isSelected()) ? tm->getTextureByName("red") : tm->getTextureByName("white");
				SDL_RenderCopy(r, tex, NULL, obj);
				SDL_RenderPresent(r);
			}

			bool isUndoable() {
				return false;
			}
		private:
			Rectangle* mRect;
			SDL_Renderer* r;
			TextureManager* tm;
	};
}
