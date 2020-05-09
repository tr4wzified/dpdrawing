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
	
		void Draw() {
			SDL_Log("Executing command.");
			mCmd->execute(renderer, tm);
			SDL_RenderPresent(renderer);
		} 
	private:
		DrawCommand* mCmd;
		SDL_Renderer* renderer;
		TextureManager* tm;
	};
}
