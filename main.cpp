#include "main.h"
#include "SDL.h"

int main(int argc, char* argv[])
{

	const unsigned int SCREEN_WIDTH = 1280;
	const unsigned int SCREEN_HEIGHT = 720;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow
	(
		"DPDrawing",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0
	);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

	// Variables
	bool quit = false;
	bool mouseBeingHeld = false;
	SDL_Event event;
	int mouseX = 0;
    int mouseY = 0;

	SDL_Rect dstrect = { 128, 128, 64, 64 };
	SDL_Surface * image = SDL_LoadBMP("resources/images/harald.bmp");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
	unsigned int sizeX;
	unsigned int sizeY;
	int mouseEndX = 0;
	int mouseEndY = 0;

    while (!quit) {
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_KEYDOWN:
				quit = true;
				break;
			case SDL_MOUSEBUTTONUP: 
				if(event.button.button == SDL_BUTTON_LEFT)
				{
							SDL_GetMouseState(&mouseEndX, &mouseEndY);
							SDL_Log("mouse end x: %d", mouseEndX);
							SDL_Log("mouse end y: %d", mouseEndY);
							sizeX = abs(mouseX - mouseEndX);
							sizeY = abs(mouseY - mouseEndY);
							SDL_Log("size x: %d", sizeX);
							SDL_Log("size y: %d", sizeY);
							dstrect = { mouseX, mouseY, sizeX, sizeY };
							SDL_RenderClear(renderer);
							SDL_RenderCopy(renderer, texture, NULL, &dstrect);
							SDL_RenderPresent(renderer);
							mouseBeingHeld = false;
							break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:
						mouseBeingHeld = true;
						SDL_GetMouseState(&mouseX, &mouseY);
						SDL_Log("mouse x: %d", mouseX);
						SDL_Log("mouse y: %d", mouseY);
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
		}
    }
    SDL_DestroyWindow(window);
	SDL_Quit();
    return 0;
}
