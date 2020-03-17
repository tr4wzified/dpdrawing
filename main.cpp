#include "main.h"
#include "SDL.h"

int main(int argc, char* argv[])
{
	// Variables
	bool quit = false;
	SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
		"DPDrawing",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280,
		720,
		0
	);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    while (!quit) {
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_KEYDOWN:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        SDL_ShowSimpleMessageBox(0, "Mouse", "Left button was pressed!", window);
                        break;
                    case SDL_BUTTON_RIGHT:
                        SDL_ShowSimpleMessageBox(0, "Mouse", "Right button was pressed!", window);
                        break;
                    default:
                        SDL_ShowSimpleMessageBox(0, "Mouse", "Some other button was pressed!", window);
                        break;
                }
                break;
		}
    }
    SDL_DestroyWindow(window);
	SDL_Quit();
    return 0;
}
