#include "main.h"
using DPDrawing::Rectangle;

int main(int argc, char* argv[])
{
	Rectangle rec(128, 128, 128, 128);
	const unsigned int SCREEN_WIDTH = 1280;
	const unsigned int SCREEN_HEIGHT = 720;
    SDL_Init(SDL_INIT_VIDEO);
	SDL_Log("SDL Initialized");

    SDL_Window* window = SDL_CreateWindow (
		"DPDrawing",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0
	);
	SDL_Log("SDL Window created");

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

	// Variables
	bool running = true;
	bool mouseBeingHeld = false;
	SDL_Event event;
	int mouseX = 0;
	int mouseY = 0;

	SDL_Surface * image = SDL_LoadBMP("resources/images/harald.bmp");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	static int sizeX;
	static int sizeY;
	static int mouseEndX = 0;
	static int mouseEndY = 0;

	int renderedFrames = 0;
    while (running) {
		renderedFrames++;
		SDL_Log(std::to_string(renderedFrames).c_str());
		if (mouseBeingHeld) {
			SDL_GetMouseState(&mouseEndX, &mouseEndY);
			rec.setRect(mouseX, mouseY, mouseEndX, mouseEndY);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture, NULL, rec.getSDLObj());
			SDL_RenderPresent(renderer);
		}
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_MOUSEBUTTONUP: 
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:
						SDL_GetMouseState(&mouseEndX, &mouseEndY);
						rec.setRect(mouseX, mouseY, mouseEndX, mouseEndY);
						SDL_RenderClear(renderer);
						SDL_RenderCopy(renderer, texture, NULL, rec.getSDLObj());
						SDL_RenderPresent(renderer);
						mouseBeingHeld = false;
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
                        SDL_ShowSimpleMessageBox(0, "Mouse", "Right button was pressed!", window);
						SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
						SDL_RenderClear(renderer);
						SDL_RenderPresent(renderer);
                        break;

                    default:
                        SDL_ShowSimpleMessageBox(0, "Mouse", "Some other button was pressed!", window);
                        break;
                }
                break;

			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					case SDLK_RETURN:
						break;
					case SDLK_e:
						SDL_Log("SDLK_e called! Exiting.");
						running = false;
						break;
					default:
						break;
				}
				break;
		}
    }
	SDL_Log("Quitting");
    SDL_DestroyWindow(window);
	SDL_Quit();
    return 0;
}
