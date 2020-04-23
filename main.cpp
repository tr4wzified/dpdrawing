#include "main.h"

SDL_Window* sdlWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
// Variables
bool running = true;
SDL_Event event;
// Mouse
int mouseX = 0;
int mouseY = 0;
int mouseEndX = 0;
int mouseEndY = 0;
bool mouseBeingHeld = false;
const vector<SDL_Surface*> images = {
    SDL_LoadBMP("resources/images/harald.bmp")
};
vector<SDL_Texture*> textures;
// Objects
Rectangle rec(128, 128, 128, 128);
// Debug
int renderedFrames = 0;

int Init(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Log("SDL Initialized");
    sdlWindow = SDL_CreateWindow("DPDrawing", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
	SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
    SDL_Log("SDL Window created");

    gRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);
    SDL_RenderPresent(gRenderer);
    // Load images into textures
    for (SDL_Surface* image : images) {
		textures.push_back(SDL_CreateTextureFromSurface(gRenderer, image));
		SDL_FreeSurface(image);
    }
    return 0;
}

int Quit()
{
    SDL_Log("Quit() called!");
    running = false;
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
    return 0;
}

void Update(SDL_Window*& sdlWindow, SDL_Renderer*& gRenderer)
{
	while (running) {
		SDL_WaitEvent(&event);
		// Live preview of the Rectangle drawing
		if (mouseBeingHeld) {
		    SDL_GetMouseState(&mouseEndX, &mouseEndY);
		    rec.setRect(mouseX, mouseY, mouseEndX, mouseEndY);
		    SDL_RenderClear(gRenderer);
		    SDL_RenderCopy(gRenderer, textures[0], NULL, rec.getSDLObj());
		    SDL_RenderPresent(gRenderer);
	}

	switch (event.type) {
		case SDL_QUIT:
		    Quit();
		    break;
		case SDL_MOUSEBUTTONUP:
		    switch (event.button.button) {
		    case SDL_BUTTON_LEFT:
			mouseBeingHeld = false;
			SDL_GetMouseState(&mouseEndX, &mouseEndY);
			rec.setRect(mouseX, mouseY, mouseEndX, mouseEndY);
			SDL_RenderClear(gRenderer);
			SDL_RenderCopy(gRenderer, textures[0], NULL, rec.getSDLObj());
			SDL_RenderPresent(gRenderer);
			break;
		    case SDL_BUTTON_RIGHT:
			SDL_GetMouseState(&mouseX, &mouseY);
			Pixel p(mouseX, mouseY, 255, 0, 0, 255);
			p.Draw(gRenderer);
			break;
		    }
		    break;
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
		    case SDL_BUTTON_LEFT:
			mouseBeingHeld = true;
			SDL_GetMouseState(&mouseX, &mouseY);
			break;

		    case SDL_BUTTON_RIGHT:
			SDL_GetMouseState(&mouseX, &mouseY);
			//Pixel p(mouseX, mouseY, 255, 0, 0, 255);
			//p.Draw(gRenderer);
			break;
		    }
		    break;

		case SDL_KEYUP:
		    switch (event.key.keysym.sym) {
				case SDLK_RETURN:
				break;
		    	case SDLK_e:
				SDL_Log("SDLK_e called! Exiting.");
				Quit();
				break;
		    	default:
				break;
		    }
		    break;
		}
    }
}

int main(int argc, char* argv[])
{
    SDL_Log("Calling Init()");
    Init(1280, 720);
    SDL_Log("Calling Update()");
    Update(sdlWindow, gRenderer);
}
