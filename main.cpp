#include "main.h"
#include<stdlib.h>
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
	static int sizeX;
	static int sizeY;
	static int mouseEndX = 0;
	static int mouseEndY = 0;

    while (!quit) {
		if(mouseBeingHeld)
		{
			SDL_GetMouseState(&mouseEndX, &mouseEndY);
			sizeX = abs(mouseX - mouseEndX);
			sizeY = abs(mouseY - mouseEndY);
			if (mouseX < mouseEndX && mouseY < mouseEndY)
			{
				dstrect = { mouseX, mouseY, sizeX, sizeY };
			}
			else if (mouseEndX < mouseX && mouseY < mouseEndY)
			{
				dstrect = { mouseEndX, mouseY, sizeX, sizeY };
			}
			else if (mouseX < mouseEndX && mouseEndY < mouseY)
			{
				dstrect = { mouseX, mouseEndY, sizeX, sizeY };
			}
			else
			{
				dstrect = { mouseEndX, mouseEndY, sizeX, sizeY };
			}
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture, NULL, &dstrect);
			SDL_RenderPresent(renderer);
		}
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_KEYDOWN:
				quit = true;
				break;
			case SDL_MOUSEBUTTONUP: 
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
						SDL_GetMouseState(&mouseEndX, &mouseEndY);
						sizeX = abs(mouseX - mouseEndX);
						sizeY = abs(mouseY - mouseEndY);
						if (mouseX < mouseEndX && mouseY < mouseEndY)
						{
							dstrect = { mouseX, mouseY, sizeX, sizeY };
						}
						else if (mouseEndX < mouseX && mouseY < mouseEndY)
						{
							dstrect = { mouseEndX, mouseY, sizeX, sizeY };
						}
						else if (mouseX < mouseEndX && mouseEndY < mouseY)
						{
							dstrect = { mouseX, mouseEndY, sizeX, sizeY };
						}
						else
						{
							dstrect = { mouseEndX, mouseEndY, sizeX, sizeY };
						}
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
