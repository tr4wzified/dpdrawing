#pragma once
#include "DrawCommand.h"
#include "TextureManager.h"
// Invoker
namespace DPDrawing {
	class Drawer {
	public:

		Drawer(SDL_Renderer* renderer, TextureManager* tm) {
			SDL_Log("Initializing Drawer");
			this->renderer = renderer;
			this->tm = tm;
		};

		void prepareToDraw(DrawCommand* cmd) {
			SDL_Log("Preparing to draw...");
			mCmd = cmd;
		}

		void updateMouse() {
			SDL_GetMouseState(&mouseX, &mouseY);
		}

		void updateMouseEnd() {
			SDL_GetMouseState(&mouseEndX, &mouseEndY);
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
			SDL_Log("Executing command.");
			mCmd->execute(renderer, tm, mouseX, mouseY, mouseEndX, mouseEndY);
			SDL_RenderPresent(renderer);
		} 
	private:
		DrawCommand* mCmd;
		SDL_Renderer* renderer;
		TextureManager* tm;
		int mouseX = 0;
		int mouseY = 0;

		int mouseEndX = 0;
		int mouseEndY = 0;
	};
}
