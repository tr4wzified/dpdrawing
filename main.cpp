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
TextureManager tm;
Invoker* dr;
MouseHandler* mh;
vector<std::unique_ptr<Shape>> shapes;
int holdingShape = -1;
// Fonts, initialized in Init()

/*void dynamicResize(Circle* mCirc) {
	int temp;
	int mouseX = mh->getMouseX();
	int mouseY = mh->getMouseY();
	int mouseEndX = mh->getMouseEndY();
	int mouseEndY = mh->getMouseEndY();
	// topleft to bottomright
    if (mouseEndX > mouseX && mouseEndY > mouseY) {
	}
	// bottomleft to topright
    else if (mouseEndX > mouseX && mouseEndY < mouseY) {
		int temp = mouseY;
		mouseY = mouseEndY;
		mouseEndY = temp;
	}
	// bottomright to topleft
    else if (mouseEndX < mouseX && mouseEndY < mouseY) {
		temp = mouseX;
		mouseX = mouseEndX;
		mouseEndX = temp;

		temp = mouseY;
		mouseY = mouseEndY;
		mouseEndY = temp;
	}
	// topright to bottomleft
	else {
		temp = mouseX;
		mouseX = mouseEndX;
		mouseEndX = temp;
    }
	int w = mouseEndX - mouseX;
	int h = mouseEndY - mouseY;
	mCirc->setWidth(w);
	mCirc->setHeight(h);

	int middelX = (mouseX + mouseEndX) / 2;
	int middelY = (mouseY + mouseEndY) / 2;
	mCirc->setCenterX(middelX); 
	mCirc->setCenterY(middelY); 
}
*/

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

int loadButtons() {
	SDL_Color text = {255,255,255};
	TTF_Font* font = TTF_OpenFont("./resources/fonts/open-sans/OpenSans-Regular.ttf", 96);
	SDL_Texture* button_tex = tm.getTextureByName("button");
	SDL_Texture* button_active = tm.getTextureByName("button-active");

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

	return 0;
}

int clearCanvas() {
	SDL_Color color = {0, 0, 0};
	dr->setDrawingColor(color);
	SDL_RenderClear(gRenderer);
	SDL_Color white = {255, 255, 255};
	dr->setDrawingColor(white);
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


void saveCanvas() {
	json jsonObjects = json::array();
	for(int i = 0; i < shapes.size(); ++i) {
	    jsonObjects.push_back(json::object());
		jsonObjects[i]["type"] = shapes.at(i)->getType();
		jsonObjects[i]["width"] = shapes.at(i)->getWidth();
		jsonObjects[i]["height"] = shapes.at(i)->getHeight();
		jsonObjects[i]["posX"] = shapes.at(i)->getPosX();
		jsonObjects[i]["posY"] = shapes.at(i)->getPosY();
	}

	std::cout << jsonObjects << std::endl;
	std::ofstream myfile(SAVE_PATH);
	myfile << jsonObjects;
	myfile.close();
}

void drawShapes() {
	for(int i = shapes.size() - 1; i >= 0; i--) {
		auto& sp = shapes.at(i);
		sp->Deselect();
		if(sp->getType() == "Rectangle") {
			DrawRectangle drawrec(dynamic_cast<Rectangle*>(sp.get()), gRenderer, &tm);
			dr->addCommand(&drawrec);
		}
		else if(sp->getType() == "Circle") {
			DrawCircle drawcirc(dynamic_cast<Circle*>(sp.get()), gRenderer, &tm);
			dr->addCommand(&drawcirc);
		}
	}
	dr->Invoke();
}

void deleteShape() {
	for(int i = 0; i < shapes.size(); i++) {
		if(shapes.at(i)->getType() == "Rectangle") {
			if (shapes.at(i)->isSelected()){
				shapes.erase(shapes.begin() + i);
				break;
			}
		}
		else if(shapes.at(i)->getType() == "Circle") {
			if (shapes.at(i)->isSelected()) {
				shapes.erase(shapes.begin() + i);
				break;
			}
		}
	}
	clearCanvas();
	drawShapes();
}

void loadCanvas() {
	std::ifstream i(SAVE_PATH);
	json j;
	i >> j;
	resetCanvas();
	SDL_Color c = {255, 255, 255};
	dr->setDrawingColor(c);
	for(int i = 0; i < (int)j.size(); ++i) {
		if (j[i]["type"].get<std::string>() == "Rectangle") {
			Rectangle r = Rectangle(j[i]["width"].get<int>(), j[i]["height"].get<int>(), j[i]["posX"].get<int>(), j[i]["posY"].get<int>());
			shapes.push_back(std::make_unique<Rectangle>(r));
			DrawRectangle drawrec(&r, gRenderer, &tm);
			dr->addCommand(&drawrec);
		}
		else if (j[i]["type"].get<std::string>() == "Circle") {
			Circle r = Circle(j[i]["width"].get<int>(), j[i]["height"].get<int>(), j[i]["posX"].get<int>() + (j[i]["width"].get<int>() / 2), j[i]["posY"].get<int>() + (j[i]["height"].get<int>() / 2));
			shapes.push_back(std::make_unique<Circle>(r));
			DrawCircle drawcirc(&r, gRenderer, &tm);
			dr->addCommand(&drawcirc);
		}
	}
	drawShapes();
	i.close();
}

void resize() {
	SDL_Log("Called resize()");
	int holdingPosX = mh->getHoldingPosX();
	int holdingPosY = mh->getHoldingPosY();
	for(int i = 0; i < shapes.size(); i++) {
		auto& sp = shapes.at(i);
		if(sp->isSelected()) {
			int centerX = sp->getWidth() / 2;
			int centerY = sp->getHeight() / 2;
			SDL_Log("centerX %d, centerY %d", centerX, centerY);
			if(sp->getType() == "Rectangle" ) {
				// top left area
				if(holdingPosX < centerX && holdingPosY < centerY) {
					SDL_Log("Resizing from top left.");
					int previousPosY = sp->getPosY();
					int previousPosX = sp->getPosX();
					sp->setPosX(mh->getMouseEndX());
					sp->setPosY(mh->getMouseEndY());
					sp->setWidth(sp->getWidth() + (previousPosX - mh->getMouseEndX()));
					sp->setHeight(sp->getHeight() + (previousPosY - mh->getMouseEndY()));
				}
				// bottom left area
				if(holdingPosX < centerX && holdingPosY > centerY) {
					SDL_Log("Resizing from bottom left.");
					int previousPosX = sp->getPosX();
					sp->setPosX(mh->getMouseEndX());
					sp->setWidth(sp->getWidth() + (previousPosX - sp->getPosX()));
					sp->setHeight(sp->getHeight() + (mh->getMouseEndY() - mh->getMouseY()));
				}
				// top right area
				if(holdingPosX > centerX && holdingPosY < centerY) {
					SDL_Log("Resizing from top right.");
					int previousPosY = sp->getPosY();
					sp->setPosY(mh->getMouseEndY());
					sp->setHeight(sp->getHeight() + (previousPosY - sp->getPosY()));
					sp->setWidth(sp->getWidth() + (mh->getMouseEndX() - mh->getMouseX()));
				}
				// bottom right
				if(holdingPosX > centerX && holdingPosY > centerY) {
					SDL_Log("Resizing from bottom right.");
					sp->setWidth(sp->getWidth() + (mh->getMouseEndX() - mh->getMouseX()));
					sp->setHeight(sp->getHeight() + (mh->getMouseEndY() - mh->getMouseY()));
				}
			}
			else if(sp->getType() == "Circle" ) {
				Circle* circ = dynamic_cast<Circle*>(sp.get());
				centerX = sp->getWidth() / 2;
				centerY = sp->getHeight() / 2;
				// top left area
				if(holdingPosX < centerX && holdingPosY < centerY) {
					SDL_Log("Resizing from top left.");
					int previousPosY = circ->getPosY();
					int previousPosX = circ->getPosX();
					circ->setPosX(mh->getMouseEndX());
					circ->setPosY(mh->getMouseEndY());
					circ->setWidth(circ->getWidth() + (previousPosX - mh->getMouseEndX()));
					circ->setHeight(circ->getHeight() + (previousPosY - mh->getMouseEndY()));
				}
				// bottom left area
				if(holdingPosX < centerX && holdingPosY > centerY) {
					SDL_Log("Resizing from bottom left.");
					int previousPosX = circ->getPosX();
					circ->setPosX(mh->getMouseEndX());
					// teveel naar onder
					circ->setWidth(circ->getWidth() + (previousPosX - circ->getPosX()));
					circ->setHeight(circ->getHeight() + ((mh->getMouseEndY() - mh->getMouseY()) / 2));
				}
				// top right area
				if(holdingPosX > centerX && holdingPosY < centerY) {
					SDL_Log("Resizing from top right.");
					int previousPosY = circ->getPosY();
					circ->setPosY(mh->getMouseEndY());
					// teveel naar rechts
					circ->setHeight(circ->getHeight() + (previousPosY - circ->getPosY()));
					circ->setWidth(circ->getWidth() + ((mh->getMouseEndX() - mh->getMouseX()) / 2));
				}
				// bottom right
				if(holdingPosX > centerX && holdingPosY > centerY) {
					SDL_Log("Resizing from bottom right.");
					int previousPosY = circ->getPosY();
					circ->setWidth(circ->getWidth() + ((mh->getMouseEndX() - mh->getMouseX()) / 2));
					circ->setHeight(circ->getHeight() + (mh->getMouseEndY() - mh->getMouseY()));
				}
			}
		}
	}
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
				saveCanvas();
				loadButtons();
				return true;
			}
			// Load
			else if(mouseY <= BUTTON_HEIGHT * 4) {
				currentMode = -3;
				loadButtons();
				loadCanvas();
				return true;
			}
			else if(mouseY <= BUTTON_HEIGHT * 5) {
				currentMode = -4;
				loadButtons();
				deleteShape();
				return true;
			}
			else if(mouseY <= BUTTON_HEIGHT * 6) {
				currentMode = -5;
				loadButtons();
				return true;
			}
		}
	//}
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
    tm.addSurface(gRenderer, "resources/images/white.bmp", "white");
    tm.addSurface(gRenderer, "resources/images/red.bmp", "red");
	tm.addSurface(gRenderer, "resources/images/button.bmp", "button");
	tm.addSurface(gRenderer, "resources/images/button-active.bmp", "button-active");
    SDL_Log("Textures loaded.");

	dr = new Invoker(gRenderer, &tm);
	mh = new MouseHandler();

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
	/* std::cout << "mouseX: " << mh->getMouseX() << " mouseY: " << mh->getMouseY() << std::endl; */
	/* std::cout << "mouseEndX: " << mh->getMouseEndX() << " mouseEndY: " << mh->getMouseEndY() << std::endl; */
	/* std::cout << "mouseBeingHeld: " << mh->getMouseBeingHeld() << std::endl; */
	SDL_WaitEvent(&event);
	mh->Update();
	//SDL_Log("mh mouseX: %d mh mouseY: %d mh mouseBeingHeld: %d", mh->getMouseX(), mh->getMouseY(), mh->getHowLongBeingHeld());
	// Live preview of the Rectangle drawing
	/*
	if (mh->getMouseBeingHeld()) {
		mh->Update();
		if(!checkIfButtonPressed()) {
			switch(currentMode) {
				// Rectangle
				case 1:
					{
						resetCanvas();
						dr->updateMouseEnd();
						int mX = dr->getMouseX();
						int mY = dr->getMouseY();
						int mEndX = dr->getMouseEndX();
						int mEndY = dr->getMouseEndY();
						Rectangle rec = Rectangle(mEndX - mX, mEndY - mY, mX, mY);
						DrawRectangle* drawrec = new DrawRectangle(&rec);
						dr->addCommand(drawrec);
						dr->Invoke();
					}
					break;
				case 2:
					{
						resetCanvas();
						dr->updateMouseEnd();
						int mX = dr->getMouseX();
						int mY = dr->getMouseY();
						int mEndX = dr->getMouseEndX();
						int mEndY = dr->getMouseEndY();
						Circle circ = Circle(mEndX - mX, mEndY - mY, mX, mY);
						std::unique_ptr<Shape> uniqueCirc = std::make_unique<Shape>(&circ);
						shapes.push_back(uniqueCirc);
						DrawCircle drawcirc = DrawCircle(&circ);
						dr->addCommand(&drawcirc);
						dr->Invoke();
					}
					break;
			}
		}
	}
	*/

	switch (event.type) {
	case SDL_QUIT:
	    Quit();
	    break;
	case SDL_MOUSEBUTTONUP:
		// Move
		if(currentMode == -1 && mh->getHowLongBeingHeld() > 30 && holdingShape >= 0) {
			if(shapes.at(holdingShape)->getType() != "Circle") {
				shapes.at(holdingShape)->setPosX(mh->getMouseEndX() - mh->getHoldingPosX());
				shapes.at(holdingShape)->setPosY(mh->getMouseEndY() - mh->getHoldingPosY());
			}
			else {
				Circle* c = dynamic_cast<Circle*>(shapes.at(holdingShape).get());
				c->setCenterX((mh->getMouseEndX() - mh->getHoldingPosX()) + c->getWidth() / 2);
				c->setCenterY((mh->getMouseEndY() - mh->getHoldingPosY()) + c->getHeight() / 2);
			}
			clearCanvas();
			drawShapes();
			holdingShape = -1;
		}

		if(currentMode == -5 && mh->getHowLongBeingHeld() > 30) {
			resize();
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
						DrawRectangle drawrec(&rec, gRenderer, &tm);
						dr->addCommand(&drawrec);
						dr->Invoke();
						break;
					}
				// Ellipse
				case 2:
					{
						Circle circ = Circle(mEndX - mX, mEndY - mY, mX, mY);
						SDL_Log("Circle posX: %d posY: %d width: %d height: %d", circ.getPosX(), circ.getPosY(), circ.getWidth(), circ.getHeight());
						dynamicResize(&circ);
						SDL_Log("Dynamic RESIZED Circle posX: %d posY: %d width: %d height: %d", circ.getPosX(), circ.getPosY(), circ.getWidth(), circ.getHeight());
						shapes.push_back(std::make_unique<Circle>(circ));
						DrawCircle drawcirc(&circ, gRenderer, &tm);
						dr->addCommand(&drawcirc);
						dr->Invoke();
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
											DrawRectangle drawrec(dynamic_cast<Rectangle*>(sp.get()), gRenderer, &tm);
											dr->addCommand(&drawrec);
											dr->Invoke();
										}
										else if(sp->getType() == "Circle") {
											DrawCircle drawrec(dynamic_cast<Circle*>(sp.get()), gRenderer, &tm);
											dr->addCommand(&drawrec);
											dr->Invoke();
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
												DrawRectangle drawrec(dynamic_cast<Rectangle*>(sp.get()), gRenderer, &tm);
												dr->addCommand(&drawrec);
												dr->Invoke();
											}
											else if(sp->getType() == "Circle") {
												DrawCircle drawcirc(dynamic_cast<Circle*>(sp.get()), gRenderer, &tm);
												dr->addCommand(&drawcirc);
												dr->Invoke();
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
