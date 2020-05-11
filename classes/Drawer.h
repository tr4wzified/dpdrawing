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

		int* updateMousePos1() {
			SDL_GetMouseState(&mousePos1[0], &mousePos1[1]);
			return mousePos1;
		}

		int* updateMousePos2() {
			SDL_GetMouseState(&mousePos2[0], &mousePos2[1]);
			return mousePos2;
		}

		int* getMousePos1() {
			return mousePos1;
		}

		int* getMousePos2() {
			return mousePos2;
		}

		void Draw() {
			SDL_Log("Executing command.");
			mCmd->execute(renderer, tm, mousePos1, mousePos2);
			SDL_RenderPresent(renderer);
		} 
	private:
		DrawCommand* mCmd;
		SDL_Renderer* renderer;
		TextureManager* tm;
		int mousePos1[2];
		int mousePos2[2];
	};
}
