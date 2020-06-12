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
		const int* BUTTON_WIDTH = nullptr;
		const int* BUTTON_HEIGHT = nullptr;
		ClearCommand* clearc = nullptr;

		public:
		ResetCommand(Invoker* inv, SDL_Renderer* renderer, TTF_Font* font, TextureManager* tm, vector<std::unique_ptr<Shape>>* shapes, int* currentMode, const int* BUTTON_WIDTH, const int* BUTTON_HEIGHT) {
			this->inv = inv;
			this->renderer = renderer;
			this->font = font;
			this->tm = tm;
			this->shapes = shapes;
			this->currentMode = currentMode;
			this->BUTTON_WIDTH = BUTTON_WIDTH;
			this->BUTTON_HEIGHT = BUTTON_HEIGHT;
		}
		~ResetCommand() {
			delete clearc;
		}
		void execute() {
			clearc = new ClearCommand(inv, renderer, font, tm, shapes, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
			inv->addCommand(clearc);
			*currentMode = 0;
			shapes->clear();
		}
		bool isUndoable() {
			return false;
		}
	};
}
