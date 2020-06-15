#include "main.h"
#define SAVE_PATH "saves/saved.json"
SDL_Window* window = nullptr;
SDL_Renderer* gRenderer = nullptr;
// Variables
bool running = true;
SDL_Event event;
/*
 * -4 = Delete Selected
 * -3 = JSON Load
 * -2 = JSON Save
 * -1 = Select
 * 0 = None (Default)
 * 1 = Rectangle
 * 2 = Circle
*/
// const
const int BUTTON_WIDTH = 75;
const int BUTTON_HEIGHT = 75;
// Objects
int currentMode = 0;
TextureManager* tm = nullptr;
Invoker* inv = nullptr;
MouseHandler* mh = nullptr;
vector<std::unique_ptr<Shape>> shapes;
int holdingShape = -1;
TTF_Font* font = nullptr;
ButtonHandler* bh = nullptr;
UndoHandler* uh = nullptr;

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
	tm = new TextureManager();

    tm->addSurface(gRenderer, "resources/images/harald.bmp", "harald");
    tm->addSurface(gRenderer, "resources/images/blue.bmp", "blue");
    tm->addSurface(gRenderer, "resources/images/white.bmp", "white");
    tm->addSurface(gRenderer, "resources/images/red.bmp", "red");
	tm->addSurface(gRenderer, "resources/images/button.bmp", "button");
	tm->addSurface(gRenderer, "resources/images/button-active.bmp", "button-active");
    SDL_Log("Textures loaded.");

	font = TTF_OpenFont("./resources/fonts/open-sans/OpenSans-Regular.ttf", 96);
	if(font == nullptr) {
		SDL_Log("ERROR: Font is NULLPTR after initializing! You're likely in the wrong directory!");
	}

	uh = new UndoHandler(gRenderer, font, tm, &shapes, &currentMode, &BUTTON_WIDTH, &BUTTON_HEIGHT);
	inv = new Invoker(gRenderer, uh);
	mh = MouseHandler::getInstance();

	bh = new ButtonHandler(inv, gRenderer, tm, uh, mh, &shapes, font, &currentMode, &BUTTON_WIDTH, &BUTTON_HEIGHT);
	LoadButtonsCommand* lbc = new LoadButtonsCommand(gRenderer, font, tm, &currentMode, &BUTTON_WIDTH, &BUTTON_HEIGHT);
	inv->addCommand(lbc);
	inv->Invoke();

    return 0;
}

int Quit() {
    SDL_Log("Quit() called!");
    running = false;
	delete mh;
	delete inv;
	delete bh;
    TTF_Quit();
	SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void Update(SDL_Window*& window, SDL_Renderer*& gRenderer) {
    while (running) {
	SDL_WaitEvent(&event);
	mh->Update();

	switch (event.type) {
	case SDL_QUIT:
	    Quit();
	    break;
	case SDL_MOUSEBUTTONUP:
		// Move
		if(currentMode == -1 && mh->getHowLongBeingHeld() > 30 && holdingShape >= 0) {
			int x = mh->getMouseEndX() - mh->getHoldingPosX();
			int y = mh->getMouseEndY() - mh->getHoldingPosY();
			MoveCommand* mc = new MoveCommand(shapes.at(holdingShape).get(), x, y);
			ClearCommand* clearc = new ClearCommand(inv, gRenderer, font, tm, &shapes, &currentMode, &BUTTON_WIDTH, &BUTTON_HEIGHT);
			DrawShapesCommand* dsc = new DrawShapesCommand(inv, tm, &shapes, gRenderer);
			inv->addCommand(mc);
			inv->addCommand(clearc);
			inv->addCommand(dsc);
			inv->Invoke();
			holdingShape = -1;
		}

		// Resize
		if(currentMode == -5 && mh->getHowLongBeingHeld() > 30) {
			Shape* s = nullptr;
			for(int i = 0; i < (int)shapes.size(); i++) {
				if(shapes.at(i)->isSelected()) {
					s = shapes.at(i).get();
				}
			}
			if(s != nullptr) {
				ResizeCommand* rc = new ResizeCommand(s, mh);
				ClearCommand* clearc = new ClearCommand(inv, gRenderer, font, tm, &shapes, &currentMode, &BUTTON_WIDTH, &BUTTON_HEIGHT);
				DrawShapesCommand* dsc = new DrawShapesCommand(inv, tm, &shapes, gRenderer);
				inv->addCommand(rc);
				inv->addCommand(clearc);
				inv->addCommand(dsc);
				inv->Invoke();
			}
		}
		mh->updateMouseBeingHeld();
	    switch (event.button.button) {
	    case SDL_BUTTON_LEFT:
		if(!bh->checkIfButtonPressed(true)) {
			switch(currentMode) {
				// Rectangle
				case 1:
					{
						CreateRectangleCommand* crc = new CreateRectangleCommand(inv, &shapes, mh, gRenderer, tm, true);
						DrawShapesCommand* dsc = new DrawShapesCommand(inv, tm, &shapes, gRenderer);
						inv->addCommand(crc);
						inv->addCommand(dsc);
						inv->Invoke();
						break;
					}
				// Ellipse
				case 2:
					{
						CreateCircleCommand* ccc = new CreateCircleCommand(inv, &shapes, mh, gRenderer, tm, true);
						DrawShapesCommand* dsc = new DrawShapesCommand(inv, tm, &shapes, gRenderer);
						inv->addCommand(ccc);
						inv->addCommand(dsc);
						inv->Invoke();
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
		mh->updateMouseBeingHeld();
		if(!bh->checkIfButtonPressed(false)) {
			switch(event.button.button) {
				case SDL_BUTTON_LEFT:
					{
						// If in selecting or resizing mode
						if(currentMode == -1 || currentMode == -5) {
							int mX = mh->getMouseX();
							int mY = mh->getMouseY();
							SDL_Log("amount of shapes %d", (int)shapes.size());
								for(unique_ptr<Shape>& s : shapes) {
									s->Deselect();
								}
								for(int i = 0; i < shapes.size(); i++) {
									if (
										mX >= shapes.at(i)->getPosX() &&
										mX <= shapes.at(i)->getPosX() + shapes.at(i)->getWidth() &&
										mY >= shapes.at(i)->getPosY() &&
										mY <= shapes.at(i)->getPosY() + shapes.at(i)->getHeight()
										) {

									SDL_Log("selecting shape %d", i);
										shapes.at(i)->Select();

										if(mh->getHowLongBeingHeld() == 0) {
											mh->updateHoldingPos(mh->getMouseX() - shapes.at(i)->getPosX(), mh->getMouseY() - shapes.at(i)->getPosY());
											holdingShape = i;
											break;
										}
									}
								}
							for(int i = 0; i < shapes.size(); i++) {
								SDL_Log("Shape %d", i);
								SDL_Log("	Selected? %d", shapes.at(i)->isSelected());
							}
							DrawShapesCommand* dsc = new DrawShapesCommand(inv, tm, &shapes, gRenderer, false);
							inv->addCommand(dsc);
							inv->Invoke();
						}
					}
			}
	    	break;
		}

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
    Init(1600, 900);
    SDL_Log("DPDrawing - calling Update()");
    Update(window, gRenderer);
}
