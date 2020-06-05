#pragma once
#include <SDL2/SDL.h>
#include "Command.h"
#include "ClearCommand.h"
#include "../Invoker.h"
#include "../Rectangle.h"
#include "../Circle.h"
#include "../Shape.h"
#include <vector>
#include <memory>
#include <string>
using std::vector;
namespace DPDrawing {
	class ResetCommand : public Command {
		private:
		vector<std::unique_ptr<Shape>>* shapes = nullptr;
		Invoker* inv = nullptr;
		SDL_Renderer* renderer = nullptr;
		TTF_Font* font = nullptr;
		TextureManager* tm = nullptr;
		int* currentMode = nullptr;
		ClearCommand* clearc = nullptr;

		public:
		ResetCommand(Invoker* inv, SDL_Renderer* renderer, TTF_Font* font, TextureManager* tm, vector<std::unique_ptr<Shape>>* shapes, int* currentMode) {
			this->inv = inv;
			this->renderer = renderer;
			this->font = font;
			this->tm = tm;
			this->shapes = shapes;
			this->currentMode = currentMode;
		}
		~ResetCommand() {
			delete clearc;
		}
		void execute() {
			clearc = new ClearCommand(inv, renderer, font, tm, shapes, currentMode);
			inv->addCommand(clearc);
			*currentMode = 0;
			shapes->clear();
		}
	};
}
