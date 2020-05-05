#pragma once
#include "classes/Circle.h"
#include "classes/Pixel.h"
#include "classes/Rectangle.h"
#include "classes/TextureManager.h"
#include "classes/Button.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace DPDrawing;
using std::vector;

namespace DPDrawing {
class Main {
public:
	int resetCanvas();
	int loadButtons();
	bool checkIfButtonPressed(int mouseX, int mouseY);
    int Quit();
    int Init(const int SCREEN_WIDTH = 1280, const int SCREEN_HEIGHT = 720);
    void Update(SDL_Window*& window, SDL_Renderer*& gRenderer);
    int main(int argc, char* argv[]);
	const vector<SDL_Surface*> images;
	vector<SDL_Texture*> textures;

};
}
