#include "main.h"
#define BUTTON_WIDTH 75
#define BUTTON_HEIGHT 75
SDL_Window* window = nullptr;
SDL_Renderer* gRenderer = nullptr;
// Variables
bool running = true;
SDL_Event event;
/*
 * 0 = Rectangle
 * 1 = Circle
*/
int currentMode = 0;
// Mouse
int mouseX = 0;
int mouseY = 0;
int mouseEndX = 0;
int mouseEndY = 0;
bool mouseBeingHeld = false;
// Objects
Rectangle rec(128, 128, 128, 128);
TextureManager tm;
Drawer* dr;
// Fonts, initialized in Init()
// Debug
int updateCount = 0;

int loadButtons() {
	SDL_Log("Loading buttons");
	SDL_Color background = {84,34,34};
	SDL_Color text = {255,255,255};

	// Button 1 - Reset - 
	Button b(0, 0, background, text, 88);
	SDL_Rect* b_rect = b.getRectangle();
	SDL_Texture* b_msg = SDL_CreateTextureFromSurface(gRenderer, b.getSurface());
	SDL_Rect* b_msg_rect = b.getRectangle();
	SDL_RenderCopy(gRenderer, tm.getTextureByName("button"), NULL, b_rect);
	SDL_RenderCopy(gRenderer, b_msg, NULL, b_msg_rect);

	// Button 2 - Rectangle - R
	Button c(BUTTON_WIDTH, 0, background, text, 82);
	SDL_Rect* c_rect = c.getRectangle();
	SDL_Texture* c_msg = SDL_CreateTextureFromSurface(gRenderer, c.getSurface());
	SDL_Rect* c_msg_rect = c.getRectangle();
	SDL_RenderCopy(gRenderer, tm.getTextureByName("button"), NULL, c_rect);
	SDL_RenderCopy(gRenderer, c_msg, NULL, c_msg_rect);

	// Button 3 - Ellipse - O
	Button d(BUTTON_WIDTH * 2, 0, background, text, 79);
	SDL_Rect* d_rect = d.getRectangle();
	SDL_Texture* d_msg = SDL_CreateTextureFromSurface(gRenderer, d.getSurface());
	SDL_Rect* d_msg_rect = d.getRectangle();
	SDL_RenderCopy(gRenderer, tm.getTextureByName("button"), NULL, d_rect);
	SDL_RenderCopy(gRenderer, d_msg, NULL, d_msg_rect);

	SDL_RenderPresent(gRenderer);

	return 0;
}

int resetCanvas() {
	SDL_Log("resetCanvas() called");
	SDL_RenderClear(gRenderer);
	loadButtons();
	return 0;
}

bool checkIfButtonPressed(int mouseX, int mouseY) {
	if(!mouseBeingHeld) {
		if(mouseY >= 0 && mouseY <= BUTTON_HEIGHT) {
		// Pressed first button - RESET
			if(mouseX >= 0 && mouseX <= BUTTON_WIDTH) {
				resetCanvas();
				return true;
			}
			// Pressed second button - RECTANGLE
			else if(mouseX >= BUTTON_WIDTH * 1 && mouseX <= BUTTON_WIDTH * 2) {
				currentMode = 0;
				return true;
			}
			// Pressed third button - ELLIPSE
			else if(mouseX >= BUTTON_WIDTH * 2 && mouseX <= BUTTON_WIDTH * 3) {
				currentMode = 1;
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

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

    SDL_Log("Initializing SDL Renderer...");
    gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);
    SDL_RenderPresent(gRenderer);
    SDL_Log("SDL Renderer initialized.");

    // Add textures to TextureManager
    SDL_Log("Loading textures into TextureManager");
    tm.addSurface(gRenderer, "resources/images/harald.bmp", "harald");
    tm.addSurface(gRenderer, "resources/images/blue.bmp", "blue");
	tm.addSurface(gRenderer, "resources/images/brown.bmp", "button");
    SDL_Log("Textures loaded.");

	dr = new Drawer(gRenderer, &tm);

	loadButtons();

    return 0;
}

int Quit()
{
    SDL_Log("Quit() called!");
    running = false;
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void Update(SDL_Window*& window, SDL_Renderer*& gRenderer)
{
    while (running) {
	SDL_WaitEvent(&event);
	updateCount++;
	if(updateCount % 50 == 0) {
		SDL_Log("Update: %s", std::to_string(updateCount).c_str());
	}
	// Live preview of the Rectangle drawing
	if (mouseBeingHeld) {
		switch(currentMode) {
			case 0:
			SDL_GetMouseState(&mouseEndX, &mouseEndY);
			if(!checkIfButtonPressed(mouseEndX, mouseEndY)) {
				SDL_GetMouseState(&mouseEndX, &mouseEndY);
				rec.setRect(mouseX, mouseY, mouseEndX, mouseEndY);
				DrawRectangle* drawrec = new DrawRectangle(&rec);
				dr->prepareToDraw(drawrec);
				dr->Draw();
			}
		}
	}

	switch (event.type) {
	case SDL_QUIT:
	    Quit();
	    break;
	case SDL_MOUSEBUTTONUP:
		mouseBeingHeld = false;
	    switch (event.button.button) {
	    case SDL_BUTTON_LEFT:
		if(!checkIfButtonPressed(mouseX, mouseY)) {
			switch(currentMode) {
				// Rectangle
				case 0:
					{
						SDL_GetMouseState(&mouseEndX, &mouseEndY);
						rec.setRect(mouseX, mouseY, mouseEndX, mouseEndY);
						DrawRectangle* drawrec = new DrawRectangle(&rec);
						dr->prepareToDraw(drawrec);
						dr->Draw();
						break;
					}
				// Ellipse
				case 1:
					{
						Circle* a = new Circle();
						a->aaellipseRGBA(gRenderer, mouseX, mouseY, mouseEndX, mouseEndY, (Uint8)255, (Uint8)255, (Uint8)255, (Uint8)255);
					SDL_RenderPresent(gRenderer);
						break;
					}
			}
		}
		break;
	    case SDL_BUTTON_RIGHT:
		break;
	    }
	    break;
	case SDL_MOUSEBUTTONDOWN:
		mouseBeingHeld = true;
	    switch (event.button.button) {
	    case SDL_BUTTON_LEFT:
		SDL_GetMouseState(&mouseX, &mouseY);
		break;

	    case SDL_BUTTON_RIGHT:
		SDL_GetMouseState(&mouseX, &mouseY);
		
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
    SDL_Log("DPDrawing - calling Init()");
    Init(1280, 720);
    SDL_Log("DPDrawing - calling Update()");
    Update(window, gRenderer);
}
