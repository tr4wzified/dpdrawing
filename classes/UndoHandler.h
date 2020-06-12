#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Shape.h"
#include "Button.h"
#include "SDL2_gfx_ellipse.h"
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include "Circle.h"
#include "Rectangle.h"
#include "TextureManager.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::unique_ptr;
using std::vector;
using json = nlohmann::json;
namespace DPDrawing {
	class UndoHandler {
		public:
		UndoHandler(SDL_Renderer* renderer, TTF_Font* font, TextureManager* tm, vector<unique_ptr<Shape>>* shapes, int* currentMode, const int* BUTTON_WIDTH, const int* BUTTON_HEIGHT);
		void Update(bool clearRedo);
		void Undo();
		void Redo();

		private:
		void printTimesteps();
		void printRedoTimesteps();
		SDL_Renderer* renderer = nullptr;
		TTF_Font* font = nullptr;
		TextureManager* tm = nullptr;
		vector<unique_ptr<Shape>>* shapes;
		int* currentMode = nullptr;
		const int* BUTTON_WIDTH = nullptr;
		const int* BUTTON_HEIGHT = nullptr;
		vector<vector<Shape*>> timesteps;
		vector<vector<Shape*>> redotimesteps;

	};
}
