#include "main.h"

SDL_Window* window = nullptr;
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
TextureManager tm;
// Objects
Rectangle rec(128, 128, 128, 128);
// Debug
int renderedFrames = 0;

int Init(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT)
{
	SDL_Log("Initializing SDL...");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Log("SDL Initialized.");

    SDL_Log("Initializing SDL Window...");
    window = SDL_CreateWindow("DPDrawing", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
	SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
    SDL_Log("SDL Window initialized.");

    TTF_Init();
    SDL_Log("TTF Loader Initialized");
    TTF_Font* font = TTF_OpenFont("resources/fonts/open-sans/OpenSans-Regular.ttf", 11);
    SDL_Log("OpenSans Loaded");

	SDL_Log("Initializing SDL Renderer...");
    gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);
    SDL_RenderPresent(gRenderer);
	SDL_Log("SDL Renderer initialized.");

	// Add textures to TextureManager
	SDL_Log("Loading textures into TextureManager");
	tm.addSurface(gRenderer, "resources/images/harald.bmp", "harald");
	SDL_Log("Textures loaded.");
    return 0;
}

int Quit()
{
    SDL_Log("Quit() called!");
    running = false;
    //TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void Update(SDL_Window*& window, SDL_Renderer*& gRenderer)
{
    while (running) {
	SDL_WaitEvent(&event);
	// Live preview of the Rectangle drawing
	if (mouseBeingHeld) {
	    SDL_GetMouseState(&mouseEndX, &mouseEndY);
	    rec.setRect(mouseX, mouseY, mouseEndX, mouseEndY);
	    SDL_RenderClear(gRenderer);
	    SDL_RenderCopy(gRenderer, tm.getTextureByName("harald"), NULL, rec.getSDLObj());
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
		SDL_RenderCopy(gRenderer, tm.getTextureByName("harald"), NULL, rec.getSDLObj());
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
		Pixel p(mouseX, mouseY, 255, 0, 0, 255);
		p.Draw(gRenderer);
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
    Update(window, gRenderer);
}
