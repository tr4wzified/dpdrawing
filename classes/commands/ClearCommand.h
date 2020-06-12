#pragma once
#include <SDL2/SDL.h>
#include "Command.h"
#include "LoadButtonsCommand.h"
#include "../Invoker.h"
#include "../Rectangle.h"
#include "../Circle.h"
#include "../Shape.h"
#include <vector>
#include <memory>
#include <string>
using std::vector;
namespace DPDrawing {
	class ClearCommand : public Command {
		private:
		Invoker* inv = nullptr;
		SDL_Renderer* renderer = nullptr;
		TTF_Font* font = nullptr;
		TextureManager* tm = nullptr;
		vector<std::unique_ptr<Shape>>* shapes;
		int* currentMode = nullptr;
		const int* BUTTON_WIDTH = nullptr;
		const int* BUTTON_HEIGHT = nullptr;
		LoadButtonsCommand* lbc = nullptr;

		public:
		ClearCommand(Invoker* inv, SDL_Renderer* renderer, TTF_Font* font, TextureManager*& tm, vector<std::unique_ptr<Shape>>* shapes, int* currentMode, const int* BUTTON_WIDTH, const int* BUTTON_HEIGHT) {
			this->inv = inv;
			this->renderer = renderer;
			this->font = font;
			this->tm = tm;
			this->shapes = shapes;
			this->currentMode = currentMode;
			this->BUTTON_WIDTH = BUTTON_WIDTH;
			this->BUTTON_HEIGHT = BUTTON_HEIGHT;
		}
		~ClearCommand() {
			delete lbc;
		}
		bool isUndoable() {
			return false;
		}
		void execute() {
			if(inv == nullptr) {
				SDL_Log("ERROR: Invoker is NULLPTR!");
			}
			if(renderer == nullptr) {
				SDL_Log("ERROR: Renderer is NULLPTR!");
			}
			if(font == nullptr) {
				SDL_Log("ERROR: font is NULLPTR!");
			}
			if(tm == nullptr) {
				SDL_Log("ERROR: tm is NULLPTR!");
			}
			if(shapes == nullptr) {
				SDL_Log("ERROR: shapes is NULLPTR!");
			}
			if(currentMode == nullptr) {
				SDL_Log("ERROR: currentMode is NULLPTR!");
			}
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
			inv->addCommand(lbc);
		}
	};
}

