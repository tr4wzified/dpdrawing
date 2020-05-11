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
			void execute(SDL_Renderer* renderer, TextureManager* tm, int* mousePos1, int* mousePos2) {
				SDL_Log("Creating tempRect");
				SDL_Rect* tempRect = mRect->getSDLObj();
				SDL_Log("Executing DrawRectangle.Draw()");
				Draw(renderer, tm, tempRect, mousePos1, mousePos2);
			}
		private:
			Rectangle* mRect;
			void Draw(SDL_Renderer* renderer, TextureManager* tm, SDL_Rect* obj, int* mousePos1, int* mousePos2) {
				SDL_Log("Using dynamicResize() on Rectangle");
				dynamicResize(mousePos1[0], mousePos1[1], mousePos2[0], mousePos2[1]);
				SDL_Log("Width: %s", std::to_string(mRect->getWidth()).c_str());
				SDL_Log("Height: %s", std::to_string(mRect->getWidth()).c_str());
				SDL_Log("posX: %s", std::to_string(mRect->getPosX()).c_str());
				SDL_Log("posY: %s", std::to_string(mRect->getPosY()).c_str());
				SDL_Log("Getting harald texture");
				SDL_Texture* tempTex = tm->getTextureById(0);
				SDL_Log("Applying TextureManager texture to Rectangle");
				SDL_RenderCopy(renderer, tempTex, NULL, obj);
			}

			void dynamicResize(int mouseX, int mouseY, int mouseEndX, int mouseEndY) {
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
