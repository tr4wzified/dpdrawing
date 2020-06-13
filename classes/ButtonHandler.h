#include "MouseHandler.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <vector>

#include "commands/HardResetCommand.h"
#include "commands/LoadButtonsCommand.h"
#include "commands/DrawShapesCommand.h"
#include "commands/SaveCommand.h"
#include "commands/LoadCommand.h"
#include "commands/DeleteCommand.h"

using std::unique_ptr;
using std::vector;
namespace DPDrawing {
	class ButtonHandler {
		private:
			Invoker* inv = nullptr;
			SDL_Renderer* renderer = nullptr;
			TextureManager* tm = nullptr;
			MouseHandler* mh = nullptr;
			UndoHandler* uh = nullptr;
			TTF_Font* font = nullptr;
			vector<unique_ptr<Shape>>* shapes = nullptr;
			const int* BUTTON_WIDTH = nullptr;
			const int* BUTTON_HEIGHT = nullptr;
			int* currentMode = nullptr;
			ResetCommand* rc = nullptr;
			LoadButtonsCommand* lbc = nullptr;
			DrawShapesCommand* dsc = nullptr;
			SaveCommand* sc = nullptr;
			LoadCommand* lc = nullptr;
			DeleteCommand* dc = nullptr;
		public:
			ButtonHandler(Invoker* inv, SDL_Renderer* renderer, TextureManager* tm, UndoHandler* uh, MouseHandler* mh, vector<unique_ptr<Shape>>* shapes, TTF_Font* font, int* currentMode, const int* BUTTON_WIDTH, const int* BUTTON_HEIGHT);
			bool checkIfButtonPressed(bool execute);
			bool initializeButtons();
	};
}
