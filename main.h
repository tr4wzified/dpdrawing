#pragma once
#include "classes/Rectangle.h"
#include "classes/Circle.h"
#include "classes/TextureManager.h"
#include "classes/Button.h"
#include "classes/Invoker.h"
#include "classes/commands/Command.h"
#include "classes/MouseHandler.h"
#include "classes/ButtonHandler.h"
#include "classes/UndoHandler.h"

#include "classes/commands/DrawRectangleCommand.h"
#include "classes/commands/DrawCircleCommand.h"
#include "classes/commands/DrawShapesCommand.h"
#include "classes/commands/MoveCommand.h"
#include "classes/commands/ResizeCommand.h"
#include "classes/commands/SaveCommand.h"
#include "classes/commands/LoadCommand.h"
#include "classes/commands/DeleteCommand.h"
#include "classes/commands/ClearCommand.h"
#include "classes/commands/ResetCommand.h"
#include "classes/commands/LoadButtonsCommand.h"
#include "classes/commands/CreateRectangleCommand.h"
#include "classes/commands/CreateCircleCommand.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace DPDrawing;
using std::vector;
using json = nlohmann::json;

namespace DPDrawing {
class Main {
public:
	int resetCanvas();
	void loadButtons();
	void saveCanvas();
	void drawShapes();
	bool checkIfButtonPressed(int mouseX, int mouseY);
    int Quit();
    int Init(const int SCREEN_WIDTH = 1280, const int SCREEN_HEIGHT = 720);
    void Update(SDL_Window*& window, SDL_Renderer*& gRenderer);
    int main(int argc, char* argv[]);
	const vector<SDL_Surface*> images;
	vector<SDL_Texture*> textures;

};
}
