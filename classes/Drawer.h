#pragma once
#include "SDL2/SDL.h"
#include "DrawCommand.h"
#include "TextureManager.h"
// Invoker
namespace DPDrawing {
	class Drawer {
	public:

		Drawer(SDL_Renderer* renderer, TextureManager* tm) {
			this->renderer = renderer;
			this->tm = tm;
		};

		void setDrawingColor(SDL_Color& c) {
			this->drawingColor = c;
			SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
		}

		void prepareToDraw(DrawCommand* cmd) {
			mCmds.push_back(cmd);
		}

		void updateMouse(bool mouseBeingHeld) {
			SDL_GetMouseState(&mouseX, &mouseY);
			this->mouseBeingHeld = mouseBeingHeld;
		}

		void updateMouseEnd(bool mouseBeingHeld) {
			SDL_GetMouseState(&mouseEndX, &mouseEndY);
			this->mouseBeingHeld = mouseBeingHeld;
		}

		int getMouseX() {
			return mouseX;
		}

		int getMouseY() {
			return mouseY;
		}

		int getMouseEndX() {
			return mouseEndX;
		}

		int getMouseEndY() {
			return mouseEndY;
		}

		void Draw() {
			for(DrawCommand* mCmd : mCmds) {
				if(mCmd == nullptr) {
					SDL_Log("ERROR: Calling Draw() on a nullptr! Your DrawCommand* likely went out of scope.");
				}
				mCmd->execute(renderer, tm);
			}
			SDL_RenderPresent(renderer);
			mCmds.clear();
		} 

	private:
		bool mouseBeingHeld;
		vector<DrawCommand*> mCmds;
		SDL_Renderer* renderer;
		TextureManager* tm;
		int mouseX = 0;
		int mouseY = 0;

		int mouseEndX = 0;
		int mouseEndY = 0;

		SDL_Color drawingColor;
	};
}
