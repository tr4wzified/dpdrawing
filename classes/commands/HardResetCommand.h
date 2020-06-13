#pragma once
#include <SDL2/SDL.h>
#include "Command.h"
#include "ResetCommand.h"
#include "../UndoHandler.h"
#include "../Invoker.h"
#include "../Rectangle.h"
#include "../Circle.h"
#include "../Shape.h"
#include <vector>
#include <memory>
#include <string>
using std::vector;
namespace DPDrawing {
	class HardResetCommand : public Command {
		private:
		vector<std::unique_ptr<Shape>>* shapes = nullptr;
		Invoker* inv = nullptr;
		UndoHandler* uh = nullptr;
		SDL_Renderer* renderer = nullptr;
		TTF_Font* font = nullptr;
		TextureManager* tm = nullptr;
		int* currentMode = nullptr;
		const int* BUTTON_WIDTH = nullptr;
		const int* BUTTON_HEIGHT = nullptr;
		ResetCommand* rc = nullptr;

		public:
		HardResetCommand(Invoker* inv, UndoHandler* uh, SDL_Renderer* renderer, TTF_Font* font, TextureManager* tm, vector<std::unique_ptr<Shape>>* shapes, int* currentMode, const int* BUTTON_WIDTH, const int* BUTTON_HEIGHT) {
			this->inv = inv;
			this->uh = uh;
			this->renderer = renderer;
			this->font = font;
			this->tm = tm;
			this->shapes = shapes;
			this->currentMode = currentMode;
			this->BUTTON_WIDTH = BUTTON_WIDTH;
			this->BUTTON_HEIGHT = BUTTON_HEIGHT;
		}
		void execute() {
			ResetCommand* rc = new ResetCommand(inv, renderer, font, tm, shapes, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
			inv->addCommand(rc);
			uh->Reset();
		}
		bool isUndoable() {
			return false;
		}
	};
}
