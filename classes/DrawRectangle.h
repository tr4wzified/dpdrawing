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
				SDL_Log("Initializing DrawRectangle");
				mRect = rect;
			}
			void execute(SDL_Renderer* renderer, TextureManager* tm, int mouseX, int mouseY, int mouseEndX, int mouseEndY, bool mouseBeingHeld) {
				Draw(renderer, tm, mRect->getSDLObj(), mouseX, mouseY, mouseEndX, mouseEndY, mouseBeingHeld);
			}
		private:
			Rectangle* mRect;
			void Draw(SDL_Renderer* renderer, TextureManager* tm, SDL_Rect* obj, int mouseX, int mouseY, int mouseEndX, int mouseEndY, bool mouseBeingHeld) {
				if(!mRect->getSelected() && !mouseBeingHeld) {
					dynamicResize(mouseX, mouseY, mouseEndX, mouseEndY);
					SDL_Log("Width: %s", std::to_string(mRect->getWidth()).c_str());
					SDL_Log("Height: %s", std::to_string(mRect->getWidth()).c_str());
					SDL_Log("posX: %s", std::to_string(mRect->getPosX()).c_str());
					SDL_Log("posY: %s", std::to_string(mRect->getPosY()).c_str());
				}
				SDL_Texture* tempTex = nullptr;
				if(!mRect->getSelected()) {
					tempTex = tm->getTextureByName("white");
				}
				else {
					tempTex = tm->getTextureByName("red");
				}
				SDL_Log("Applying TextureManager texture to Rectangle");
				SDL_RenderCopy(renderer, tempTex, NULL, obj);
			}

			void dynamicResize(int mouseX, int mouseY, int mouseEndX, int mouseEndY) {
				SDL_Log("Using dynamicResize() on Rectangle");
			    if (mouseEndX > mouseX && mouseEndY > mouseY) {
					mRect->setPosX(mouseX);
					mRect->setPosY(mouseY);
				}
			    else if (mouseEndX > mouseX && mouseEndY < mouseY) {
					mRect->setPosX(mouseX);
					mRect->setPosY(mouseEndY);
				}
			    else if (mouseEndX < mouseX && mouseEndY < mouseY) {
					mRect->setPosX(mouseEndX);
					mRect->setPosY(mouseEndY);
				}
				else {
					mRect->setPosX(mouseEndX);
					mRect->setPosY(mouseY);
			    }
				mRect->setWidth(abs(mouseEndX - mouseX));
			    mRect->setHeight(abs(mouseEndY - mouseY));
			}
	};
}
