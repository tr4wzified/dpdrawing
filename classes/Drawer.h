#pragma once
#include "DrawCommand.h"
#include "TextureManager.h"
// Invoker
namespace DPDrawing {
	class Drawer {
	public:
		Drawer(SDL_Renderer* renderer, TextureManager* tm){};
		void prepareToDraw(DrawCommand* cmd) {
			mCmd = cmd;
		}
	
		void Draw() {
			mCmd->execute(renderer, tm);
		} 
	private:
		DrawCommand* mCmd;
		SDL_Renderer* renderer;
		TextureManager* tm;
	};
}
