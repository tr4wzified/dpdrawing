#pragma once
#include "SDL2/SDL.h"
#include "Command.h"
#include "TextureManager.h"
#include <memory>
// Invoker
namespace DPDrawing {
	class Invoker {
	public:
		Invoker(SDL_Renderer* renderer, TextureManager* tm);
		void setDrawingColor(SDL_Color& c);
		void addCommand(Command* cmd);
		void Invoke();

	private:
		vector<Command*> mCmds;
		SDL_Renderer* renderer;
		TextureManager* tm;
		SDL_Color drawingColor;
	};
}
