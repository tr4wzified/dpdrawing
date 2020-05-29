#pragma once
#include "SDL2/SDL.h"
#include "commands/Command.h"
#include "TextureManager.h"
#include <memory>
// Invoker
namespace DPDrawing {
	class Invoker {
	public:
		Invoker(SDL_Renderer* renderer, TextureManager* tm);
		void addCommand(Command* cmd);
		void Invoke();
		void setDrawingColor(SDL_Color& c); 

	private:
		vector<Command*> mCmds;
		SDL_Renderer* renderer;
		TextureManager* tm;
	};
}
