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
			void execute(SDL_Renderer* renderer, TextureManager* tm, int mouseX, int mouseY, int mouseEndX, int mouseEndY, bool mouseBeingHeld) {
				Draw(renderer, tm, mRect->getSDLObj(), mouseX, mouseY, mouseEndX, mouseEndY, mouseBeingHeld);
			}
		private:
			Rectangle* mRect;
			void Draw(SDL_Renderer* renderer, TextureManager* tm, SDL_Rect* obj, int mouseX, int mouseY, int mouseEndX, int mouseEndY, bool mouseBeingHeld) {
				SDL_Texture* tempTex = nullptr;
				if(!mRect->getSelected()) {
					tempTex = tm->getTextureByName("white");
				}
				else {
					tempTex = tm->getTextureByName("red");
				}
				SDL_RenderCopy(renderer, tempTex, NULL, obj);
			}

	};
}
