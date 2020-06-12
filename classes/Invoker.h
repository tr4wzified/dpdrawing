#pragma once
#include "SDL2/SDL.h"
#include "commands/Command.h"
#include "Button.h"
#include "TextureManager.h"
#include "UndoHandler.h"
#include <memory>
using std::vector;
using std::unique_ptr;
// Invoker
namespace DPDrawing {
	class Invoker {
	public:
		Invoker(SDL_Renderer* renderer, UndoHandler* uh);
		void addCommand(Command* cmd);
		void Invoke();
		void Reset();
		int timesExecuted = 0;

	private:
		vector<Command*> mCmds;
		SDL_Renderer* renderer;
		UndoHandler* uh;
	};
}
