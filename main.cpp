#include "main.h"

SDL_Window* window;
SDL_Renderer* renderer;
// Variables
bool running = true;
SDL_Event event;
// Mouse
int mouseX = 0;
int mouseY = 0;
int mouseEndX = 0;
int mouseEndY = 0;
bool mouseBeingHeld = false;
// Objects
DPDrawing::DrawRectangle rec(128, 128, 128, 128);
// Debug
int renderedFrames = 0;

int Init(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT) {
    SDL_Init(SDL_INIT_VIDEO);
	SDL_Log("SDL Initialized");
	window = SDL_CreateWindow (
		"DPDrawing",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0
	);
	SDL_Log("SDL Window created");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
	return 0;
}

int Quit() {
	running = false;
	SDL_Log("Quit() called!");
    SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void Update(SDL_Window*& window, SDL_Renderer*& renderer) {
	SDL_Surface * image = SDL_LoadBMP("resources/images/harald.bmp");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
    while (running) {
		//renderedFrames++;
		//SDL_Log(std::to_string(renderedFrames).c_str());
		// Live preview of the Rectangle drawing
		if (mouseBeingHeld) {
			SDL_GetMouseState(&mouseEndX, &mouseEndY);
			rec.setRect(mouseX, mouseY, mouseEndX, mouseEndY);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture, NULL, rec.getSDLObj());
			SDL_RenderPresent(renderer);
		}

		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_QUIT:
				Quit();
				break;
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
	Init(1280, 720);
	Update(window, renderer);
}
