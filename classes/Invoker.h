#pragma once
#include "SDL2/SDL.h"
#include "commands/Command.h"
#include "Button.h"
#include "TextureManager.h"
#include <memory>
using std::vector;
using std::unique_ptr;
// Invoker
namespace DPDrawing {
	class Invoker {
	public:
		Invoker(SDL_Renderer* renderer);
		void addCommand(Command* cmd);
		void Invoke();
		void Reset();
		void Undo(vector<unique_ptr<Shape>>* shapes, TextureManager* tm, TTF_Font* font, const int& BUTTON_WIDTH, const int BUTTON_HEIGHT, int* currentMode);
		int timesExecuted = 0;

	private:
		vector<Command*> mCmds;
		SDL_Renderer* renderer;
		vector<Command*> executedCommands;
		vector<Command*> undoneCommands;
	};
}
