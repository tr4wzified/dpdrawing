#include "main.h"
#define BUTTON_WIDTH 75
#define BUTTON_HEIGHT 75
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
int currentMode = 0;
// Objects
TextureManager* tm = nullptr;
Invoker* inv = nullptr;
MouseHandler* mh = nullptr;
vector<std::unique_ptr<Shape>> shapes;
int holdingShape = -1;
TTF_Font* font = nullptr;
// Fonts, initialized in Init()
SDL_Texture* button_tex; 
SDL_Texture* button_active;

void dynamicResize(Shape* mShape) {
	int temp;
	int mouseX = mh->getMouseX();
	int mouseY = mh->getMouseY();
	int mouseEndX = mh->getMouseEndX();
	int mouseEndY = mh->getMouseEndY();
	if (mouseEndX > mouseX && mouseEndY > mouseY) {
		mShape->setPosX(mouseX);
		mShape->setPosY(mouseY);
	}
	else if (mouseEndX > mouseX && mouseEndY < mouseY) {
		mShape->setPosX(mouseX);
		mShape->setPosY(mouseEndY);
	}
	else if (mouseEndX < mouseX && mouseEndY < mouseY) {
		mShape->setPosX(mouseEndX);
		mShape->setPosY(mouseEndY);
	}
	else {
		mShape->setPosX(mouseEndX);
		mShape->setPosY(mouseY);
	}
	mShape->setWidth(abs(mouseEndX - mouseX));
	mShape->setHeight(abs(mouseEndY - mouseY));
}


bool checkIfButtonPressed() {
	int mouseX = mh->getMouseX();
	int mouseY = mh->getMouseY();
	//if(!mouseBeingHeld) {
		// Horizontal
		if(mouseY >= 0 && mouseY <= BUTTON_HEIGHT) {
		// Pressed first button - RESET
			if(mouseX >= 0 && mouseX <= BUTTON_WIDTH) {
				currentMode = 0;
				ResetCommand resetc(inv, gRenderer, font, tm, &shapes, &currentMode);
				inv->addCommand(&resetc);
				inv->Invoke();
				return true;
			}
			// Pressed second button - RECTANGLE
			else if(mouseX >= BUTTON_WIDTH * 1 && mouseX <= BUTTON_WIDTH * 2) {
				currentMode = 1;
				LoadButtonsCommand lbc(gRenderer, font, tm, &currentMode);
				inv->addCommand(&lbc);
				inv->Invoke();
				return true;
			}
			// Pressed third button - ELLIPSE
			else if(mouseX >= BUTTON_WIDTH * 2 && mouseX <= BUTTON_WIDTH * 3) {
				currentMode = 2;
				LoadButtonsCommand lbc(gRenderer, font, tm, &currentMode);
				inv->addCommand(&lbc);
				inv->Invoke();
				return true;
			}
			return false;
		}
		// Vertical
		else if(mouseX <= BUTTON_WIDTH && mouseY >= 0) {
			// Select
			if(mouseY <= BUTTON_HEIGHT * 2) {
				currentMode = -1;
				LoadButtonsCommand lbc(gRenderer, font, tm, &currentMode);
				inv->addCommand(&lbc);
				inv->Invoke();
				return true;
			}
			// Save
			else if(mouseY <= BUTTON_HEIGHT * 3) {
				currentMode = -2;
				SaveCommand sc(&shapes, "saves/saved.json");
				inv->addCommand(&sc);
				LoadButtonsCommand lbc(gRenderer, font, tm, &currentMode);
				inv->addCommand(&lbc);
				inv->Invoke();
				return true;
			}
			// Load
			else if(mouseY <= BUTTON_HEIGHT * 4) {
				currentMode = -3;
				ResetCommand resetc(inv, gRenderer, font, tm, &shapes, &currentMode);
				LoadCommand lc(&shapes, "saves/saved.json", gRenderer);
				DrawShapesCommand dsc(inv, tm, &shapes, gRenderer);
				inv->addCommand(&resetc);
				inv->addCommand(&lc);
				inv->addCommand(&dsc);
				inv->Invoke();
				return true;
			}
			// Delete Selected
			else if(mouseY <= BUTTON_HEIGHT * 5) {
				currentMode = -4;
				LoadButtonsCommand lbc(gRenderer, font, tm, &currentMode);
				DeleteCommand dc(&shapes);
				ClearCommand clearc(inv, gRenderer, font, tm, &shapes, &currentMode);
				DrawShapesCommand dsc(inv, tm, &shapes, gRenderer);
				inv->addCommand(&lbc);
				inv->addCommand(&dc);
				inv->addCommand(&clearc);
				inv->addCommand(&dsc);
				inv->Invoke();
				return true;
			}
			else if(mouseY <= BUTTON_HEIGHT * 6) {
				currentMode = -5;
				LoadButtonsCommand lbc(gRenderer, font, tm, &currentMode);
				inv->addCommand(&lbc);
				inv->Invoke();
				return true;
			}
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
	tm = new TextureManager();

    tm->addSurface(gRenderer, "resources/images/harald.bmp", "harald");
    tm->addSurface(gRenderer, "resources/images/blue.bmp", "blue");
    tm->addSurface(gRenderer, "resources/images/white.bmp", "white");
    tm->addSurface(gRenderer, "resources/images/red.bmp", "red");
	tm->addSurface(gRenderer, "resources/images/button.bmp", "button");
	tm->addSurface(gRenderer, "resources/images/button-active.bmp", "button-active");
    SDL_Log("Textures loaded.");

	inv = new Invoker(gRenderer);
	mh = MouseHandler::getInstance();
	font = TTF_OpenFont("./resources/fonts/open-sans/OpenSans-Regular.ttf", 96);
	if(font == nullptr) {
		SDL_Log("ERROR: Font is NULLPTR after initializing!");
	}

	LoadButtonsCommand lbc(gRenderer, font, tm, &currentMode);
	inv->addCommand(&lbc);
	inv->Invoke();

    return 0;
}

int Quit() {
    SDL_Log("Quit() called!");
    running = false;
	delete mh;
	delete inv;
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
			shapes.at(holdingShape)->setPosX(mh->getMouseEndX() - mh->getHoldingPosX());
			shapes.at(holdingShape)->setPosY(mh->getMouseEndY() - mh->getHoldingPosY());
			ClearCommand clearc(inv, gRenderer, font, tm, &shapes, &currentMode);
			DrawShapesCommand dsc(inv, tm, &shapes, gRenderer);
			inv->addCommand(&clearc);
			inv->addCommand(&dsc);
			holdingShape = -1;
			inv->Invoke();
		}

		if(currentMode == -5 && mh->getHowLongBeingHeld() > 30) {
			Shape* s = nullptr;
			for(int i = 0; i < (int)shapes.size(); i++) {
				if(shapes.at(i)->isSelected()) {
					s = shapes.at(i).get();
				}
			}
			if(s != nullptr) {
				ResizeCommand rc(s, mh);
				ClearCommand clearc(inv, gRenderer, font, tm, &shapes, &currentMode);
				DrawShapesCommand dsc(inv, tm, &shapes, gRenderer);
				inv->addCommand(&rc);
				inv->addCommand(&clearc);
				inv->addCommand(&dsc);
				inv->Invoke();
			}
		}
		mh->updateMouseBeingHeld();
	    switch (event.button.button) {
	    case SDL_BUTTON_LEFT:
		if(!checkIfButtonPressed()) {
			int mX = mh->getMouseX();
			int mY = mh->getMouseY();
			int mEndX = mh->getMouseEndX();
			int mEndY = mh->getMouseEndY();
			switch(currentMode) {
				// Rectangle
				case 1:
					{
						Rectangle rec = Rectangle(mEndX - mX, mEndY - mY, mX, mY);
						dynamicResize(&rec);
						shapes.push_back(std::make_unique<Rectangle>(rec));
						DrawRectangleCommand drawrec(&rec, gRenderer, tm);
						inv->addCommand(&drawrec);
						inv->Invoke();
						break;
					}
				// Ellipse
				case 2:
					{
						Circle circ = Circle(mEndX - mX, mEndY - mY, mX, mY);
						dynamicResize(&circ);
						shapes.push_back(std::make_unique<Circle>(circ));
						DrawCircleCommand drawcirc(&circ, gRenderer, tm);
						inv->addCommand(&drawcirc);
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
		if(!checkIfButtonPressed()) {
			switch(event.button.button) {
				case SDL_BUTTON_LEFT:
					{
						if(currentMode == -1 || currentMode == -5) {
								int mX = mh->getMouseX();
								int mY = mh->getMouseY();
								int shapes_size = shapes.size();
								if (shapes_size > 0) {
									for(int i = shapes_size - 1; i >= 0; i--) {
										auto& sp = shapes.at(i);
										sp->Deselect();
										if(sp->getType() == "Rectangle") {
											DrawRectangleCommand drawrec(dynamic_cast<Rectangle*>(sp.get()), gRenderer, tm);
											inv->addCommand(&drawrec);
											inv->Invoke();
										}
										else if(sp->getType() == "Circle") {
											DrawCircleCommand drawrec(dynamic_cast<Circle*>(sp.get()), gRenderer, tm);
											inv->addCommand(&drawrec);
											inv->Invoke();
										}
									}
									for(int i = shapes_size - 1; i >= 0; i--) {
										auto& sp = shapes.at(i);
										if (
											mX >= sp->getPosX() &&
											mX <= sp->getPosX() + sp->getWidth() &&
											mY >= sp->getPosY() &&
											mY <= sp->getPosY() + sp->getHeight()
											) {

											sp->Select();

											if(mh->getHowLongBeingHeld() == 0) {
												mh->updateHoldingPos(mh->getMouseX() - sp->getPosX(), mh->getMouseY() - sp->getPosY());
												holdingShape = i;
											}

											if(sp->getType() == "Rectangle") {
												DrawRectangleCommand drawrec(dynamic_cast<Rectangle*>(sp.get()), gRenderer, tm);
												inv->addCommand(&drawrec);
												inv->Invoke();
											}
											else if(sp->getType() == "Circle") {
												DrawCircleCommand drawcirc(dynamic_cast<Circle*>(sp.get()), gRenderer, tm);
												inv->addCommand(&drawcirc);
												inv->Invoke();
											}
											break;
										}
									}
								}
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
