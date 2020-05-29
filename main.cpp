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

void loadButtons() {
	SDL_Color text = {255,255,255};

	// Button -5 - Resize - Vertical
	Button w(0, BUTTON_HEIGHT * 5, text, 124, font);
	SDL_Rect* w_rect = w.getRectangle();
	SDL_Texture* w_msg = SDL_CreateTextureFromSurface(gRenderer, w.getSurface());
	SDL_Rect* w_msg_rect = w.getRectangle();
	if(currentMode == -5) {
		SDL_RenderCopy(gRenderer, button_active, NULL, w_rect);
	}
	else {
		SDL_RenderCopy(gRenderer, button_tex, NULL, w_rect);
	}
	SDL_RenderCopy(gRenderer, w_msg, NULL, w_msg_rect);

	// Button -4 - Delete - Vertical
	Button x(0, BUTTON_HEIGHT * 4, text, 68, font);
	SDL_Rect* x_rect = x.getRectangle();
	SDL_Texture* x_msg = SDL_CreateTextureFromSurface(gRenderer, x.getSurface());
	SDL_Rect* x_msg_rect = x.getRectangle();
	if(currentMode == -4) {
		SDL_RenderCopy(gRenderer, button_active, NULL, x_rect);
	}
	else {
		SDL_RenderCopy(gRenderer, button_tex, NULL, x_rect);
	}
	SDL_RenderCopy(gRenderer, x_msg, NULL, x_msg_rect);

	// Button -3 - JSON Load - Vertical
	Button y(0, BUTTON_HEIGHT * 3, text, 76, font);
	SDL_Rect* y_rect = y.getRectangle();
	SDL_Texture* y_msg = SDL_CreateTextureFromSurface(gRenderer, y.getSurface());
	SDL_Rect* y_msg_rect = y.getRectangle();
	if(currentMode == -3) {
		SDL_RenderCopy(gRenderer, button_active, NULL, y_rect);
	}
	else {
		SDL_RenderCopy(gRenderer, button_tex, NULL, y_rect);
	}
	SDL_RenderCopy(gRenderer, y_msg, NULL, y_msg_rect);

	// Button -2 - JSON Save - Vertical
	Button z(0, BUTTON_HEIGHT * 2, text, 74, font);
	SDL_Rect* z_rect = z.getRectangle();
	SDL_Texture* z_msg = SDL_CreateTextureFromSurface(gRenderer, z.getSurface());
	SDL_Rect* z_msg_rect = z.getRectangle();
	if(currentMode == -2) {
		SDL_RenderCopy(gRenderer, button_active, NULL, z_rect);
	}
	else {
		SDL_RenderCopy(gRenderer, button_tex, NULL, z_rect);
	}
	SDL_RenderCopy(gRenderer, z_msg, NULL, z_msg_rect);

	// Button -1 - Select - Vertical
	Button a(0, BUTTON_HEIGHT, text, 83, font);
	SDL_Rect* a_rect = a.getRectangle();
	SDL_Texture* a_msg = SDL_CreateTextureFromSurface(gRenderer, a.getSurface());
	SDL_Rect* a_msg_rect = a.getRectangle();
	if(currentMode == -1) {
		SDL_RenderCopy(gRenderer, button_active, NULL, a_rect);
	}
	else {
		SDL_RenderCopy(gRenderer, button_tex, NULL, a_rect);
	}
	SDL_RenderCopy(gRenderer, a_msg, NULL, a_msg_rect);

	// Button 1 - Reset
	Button b(0, 0, text, 88, font);
	SDL_Rect* b_rect = b.getRectangle();
	SDL_Texture* b_msg = SDL_CreateTextureFromSurface(gRenderer, b.getSurface());
	SDL_Rect* b_msg_rect = b.getRectangle();
	if(currentMode == 0) {
		SDL_RenderCopy(gRenderer, button_active, NULL, b_rect);
	}
	else {
		SDL_RenderCopy(gRenderer, button_tex, NULL, b_rect);
	}
	SDL_RenderCopy(gRenderer, b_msg, NULL, b_msg_rect);

	// Button 2 - Rectangle - R
	Button c(BUTTON_WIDTH, 0, text, 82, font);
	SDL_Rect* c_rect = c.getRectangle();
	SDL_Texture* c_msg = SDL_CreateTextureFromSurface(gRenderer, c.getSurface());
	SDL_Rect* c_msg_rect = c.getRectangle();
	if(currentMode == 1) {
		SDL_RenderCopy(gRenderer, button_active, NULL, c_rect);
	}
	else {
		SDL_RenderCopy(gRenderer, button_tex, NULL, c_rect);
	}
	SDL_RenderCopy(gRenderer, c_msg, NULL, c_msg_rect);

	// Button 3 - Ellipse - O
	Button d(BUTTON_WIDTH * 2, 0, text, 79, font);
	SDL_Rect* d_rect = d.getRectangle();
	SDL_Texture* d_msg = SDL_CreateTextureFromSurface(gRenderer, d.getSurface());
	SDL_Rect* d_msg_rect = d.getRectangle();
	if(currentMode == 2) {
		SDL_RenderCopy(gRenderer, button_active, NULL, d_rect);
	}
	else {
		SDL_RenderCopy(gRenderer, button_tex, NULL, d_rect);
	}
	SDL_RenderCopy(gRenderer, d_msg, NULL, d_msg_rect);

	SDL_RenderPresent(gRenderer);

	// Destroy
	SDL_DestroyTexture(w_msg);
	SDL_DestroyTexture(x_msg);
	SDL_DestroyTexture(y_msg);
	SDL_DestroyTexture(z_msg);
	SDL_DestroyTexture(a_msg);
	SDL_DestroyTexture(b_msg);
	SDL_DestroyTexture(c_msg);
	SDL_DestroyTexture(d_msg);
}

int clearCanvas() {
	SDL_Color color = {0, 0, 0};
	inv->setDrawingColor(color);
	SDL_RenderClear(gRenderer);
	SDL_Color white = {255, 255, 255};
	inv->setDrawingColor(white);
	loadButtons();
	return 0;
}

int resetCanvas() {
	SDL_Log("resetCanvas() called");
	clearCanvas();
	currentMode = 0;
	shapes.clear();
	return 0;
}

void drawShapes() {
	for(int i = shapes.size() - 1; i >= 0; i--) {
		auto& sp = shapes.at(i);
		sp->Deselect();
		if(sp->getType() == "Rectangle") {
			DrawRectangleCommand drawrec(dynamic_cast<Rectangle*>(sp.get()), gRenderer, tm);
			inv->addCommand(&drawrec);
		}
		else if(sp->getType() == "Circle") {
			DrawCircleCommand drawcirc(dynamic_cast<Circle*>(sp.get()), gRenderer, tm);
			inv->addCommand(&drawcirc);
		}
		inv->Invoke();
	}
}

void loadCanvas() {
	std::ifstream i(SAVE_PATH);
	json j;
	i >> j;
	SDL_Color c = {255, 255, 255};
	inv->setDrawingColor(c);
	for(int i = 0; i < (int)j.size(); ++i) {
		if (j[i]["type"].get<std::string>() == "Rectangle") {
			Rectangle r = Rectangle(j[i]["width"].get<int>(), j[i]["height"].get<int>(), j[i]["posX"].get<int>(), j[i]["posY"].get<int>());
			shapes.push_back(std::make_unique<Rectangle>(r));
		}
		else if (j[i]["type"].get<std::string>() == "Circle") {
			Circle r = Circle(j[i]["width"].get<int>(), j[i]["height"].get<int>(), j[i]["posX"].get<int>(), j[i]["posY"].get<int>());
			shapes.push_back(std::make_unique<Circle>(r));
		}
	}
	i.close();
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
				resetCanvas();
				return true;
			}
			// Pressed second button - RECTANGLE
			else if(mouseX >= BUTTON_WIDTH * 1 && mouseX <= BUTTON_WIDTH * 2) {
				currentMode = 1;
				loadButtons();
				return true;
			}
			// Pressed third button - ELLIPSE
			else if(mouseX >= BUTTON_WIDTH * 2 && mouseX <= BUTTON_WIDTH * 3) {
				currentMode = 2;
				loadButtons();
				return true;
			}
			return false;
		}
		// Vertical
		else if(mouseX <= BUTTON_WIDTH && mouseY >= 0) {
			// Select
			if(mouseY <= BUTTON_HEIGHT * 2) {
				currentMode = -1;
				loadButtons();
				return true;
			}
			// Save
			else if(mouseY <= BUTTON_HEIGHT * 3) {
				currentMode = -2;
				SaveCommand sc(&shapes, "saves/saved.json");
				inv->addCommand(&sc);
				inv->Invoke();
				loadButtons();
				return true;
			}
			// Load
			else if(mouseY <= BUTTON_HEIGHT * 4) {
				currentMode = -3;
				resetCanvas();
				LoadCommand lc(&shapes, "saves/saved.json");
				inv->addCommand(&lc);
				inv->Invoke();
				drawShapes();
				return true;
			}
			// Delete Selected
			else if(mouseY <= BUTTON_HEIGHT * 5) {
				currentMode = -4;
				loadButtons();
				DeleteCommand dc(&shapes);
				inv->addCommand(&dc);
				inv->Invoke();
				clearCanvas();
				drawShapes();
				return true;
			}
			else if(mouseY <= BUTTON_HEIGHT * 6) {
				currentMode = -5;
				loadButtons();
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
	if(tm == nullptr) {
		SDL_Log("ERROR: TextureManager is NULLPTR!");
	}
    tm->addSurface(gRenderer, "resources/images/harald.bmp", "harald");
    tm->addSurface(gRenderer, "resources/images/blue.bmp", "blue");
    tm->addSurface(gRenderer, "resources/images/white.bmp", "white");
    tm->addSurface(gRenderer, "resources/images/red.bmp", "red");
	tm->addSurface(gRenderer, "resources/images/button.bmp", "button");
	tm->addSurface(gRenderer, "resources/images/button-active.bmp", "button-active");
    SDL_Log("Textures loaded.");

	inv = new Invoker(gRenderer, tm);
	mh = DPDrawing::MouseHandler::getInstance();
	font = TTF_OpenFont("./resources/fonts/open-sans/OpenSans-Regular.ttf", 96);
	if(font == nullptr) {
		SDL_Log("ERROR: Font is NULLPTR after initializing!");
	}
	button_tex = tm->getTextureByName("button");
	button_active = tm->getTextureByName("button-active");

	loadButtons();

    return 0;
}

int Quit()
{
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

void Update(SDL_Window*& window, SDL_Renderer*& gRenderer)
{
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
			clearCanvas();
			drawShapes();
			holdingShape = -1;
		}

		if(currentMode == -5 && mh->getHowLongBeingHeld() > 30) {
			Shape* s = nullptr;
			for(int i = 0; i < shapes.size(); i++) {
				if(shapes.at(i)->isSelected()) {
					s = shapes.at(i).get();
				}
			}
			ResizeCommand rc(s, mh);
			inv->addCommand(&rc);
			inv->Invoke();
			
			clearCanvas();
			drawShapes();
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
