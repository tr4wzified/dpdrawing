#pragma once
#include "SDL2/SDL.h"
#include "commands/Command.h"
#include "TextureManager.h"
#include <memory>
#include <stack>
using std::vector;
using std::stack;
// Invoker
namespace DPDrawing {
	class Invoker {
	public:
		Invoker(SDL_Renderer* renderer);
		void addCommand(Command* cmd);
		void Invoke();

	private:
		vector<Command*> mCmds;
		SDL_Renderer* renderer;
		stack<Command*> executedCommands;
		stack<Command*> undoneCommands;
	};
}
