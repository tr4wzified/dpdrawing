#include "main.h"
#define BUTTON_WIDTH 75
#define BUTTON_HEIGHT 75
#define SAVE_PATH "saves/objects.json"
SDL_Window* window = nullptr;
SDL_Renderer* gRenderer = nullptr;
// Variables
bool running = true;
SDL_Event event;
/*
 * -1 = Select
 * 0 = None
 * 1 = Rectangle
 * 2 = Circle
*/
int currentMode = 0;
// Mouse
bool mouseBeingHeld = false;
int howLongBeingHeld = 0;
int holdingPosX = 0;
int holdingPosY = 0;
// Objects
TextureManager tm;
Drawer* dr;
Shape* selectedShape = nullptr;
vector<std::unique_ptr<Shape>> shapes;
Rectangle* holdingRectangle;
// Fonts, initialized in Init()

void dynamicResize(Circle* mCirc, int mouseX, int mouseY, int mouseEndX, int mouseEndY) {
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
		int temp = mouseX;
		mouseX = mouseEndX;
		mouseEndX = temp;

		temp = mouseY;
		mouseY = mouseEndY;
		mouseEndY = temp;
	}
	// topright to bottomleft
	else {
		int temp = mouseX;
		mouseX = mouseEndX;
		mouseEndX = temp;
    }
	int radiusX = (mouseEndX - mouseX) / 2;
	int radiusY = (mouseEndY - mouseY) / 2;
	mCirc->setRadiusX(radiusX);
	mCirc->setRadiusY(radiusY);

	int middelX = (mouseX + mouseEndX) / 2;
	int middelY = (mouseY + mouseEndY) / 2;
	mCirc->setCenterX(middelX); 
	mCirc->setCenterY(middelY); 

	dr->updateMouse(mouseBeingHeld);
}

void dynamicResize(Rectangle* mRect, int mouseX, int mouseY, int mouseEndX, int mouseEndY) {
	if (mouseEndX > mouseX && mouseEndY > mouseY) {
		mRect->setPosX(mouseX);
		mRect->setPosY(mouseY);
	}
	else if (mouseEndX > mouseX && mouseEndY < mouseY) {
		mRect->setPosX(mouseX);
		mRect->setPosY(mouseEndY);
	}
	else if (mouseEndX < mouseX && mouseEndY < mouseY) {
		mRect->setPosX(mouseEndX);
		mRect->setPosY(mouseEndY);
	}
	else {
		mRect->setPosX(mouseEndX);
		mRect->setPosY(mouseY);
	}
	mRect->setWidth(abs(mouseEndX - mouseX));
	mRect->setHeight(abs(mouseEndY - mouseY));

	dr->updateMouse(mouseBeingHeld);
}

int loadButtons() {
	SDL_Color text = {255,255,255};

	// Button -4 - Delete - Vertical
	SDL_Texture* button_tex = tm.getTextureByName("button");
	SDL_Texture* button_active = tm.getTextureByName("button-active");
	Button x(0, BUTTON_HEIGHT * 4, text, 68);
	SDL_Rect* x_rect = x.getRectangle();
	SDL_Texture* x_msg = SDL_CreateTextureFromSurface(gRenderer, x.getSurface());
	SDL_Rect* x_msg_rect = x.getRectangle();
	if(currentMode == -3) {
		SDL_RenderCopy(gRenderer, button_active, NULL, x_rect);
	}
	else {
		SDL_RenderCopy(gRenderer, button_tex, NULL, x_rect);
	}
	SDL_RenderCopy(gRenderer, x_msg, NULL, x_msg_rect);

	// Button -3 - JSON Load - Vertical
	Button y(0, BUTTON_HEIGHT * 3, text, 76);
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
	Button z(0, BUTTON_HEIGHT * 2, text, 74);
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
	Button a(0, BUTTON_HEIGHT, text, 83);
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
	Button b(0, 0, text, 88);
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
	Button c(BUTTON_WIDTH, 0, text, 82);
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
	Button d(BUTTON_WIDTH * 2, 0, text, 79);
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
	SDL_Log("resetCanvas() called");
	currentMode = 0;
	SDL_Color color = {0, 0, 0};
	dr->setDrawingColor(color);
	SDL_RenderClear(gRenderer);
	SDL_Color white = {255, 255, 255};
	dr->setDrawingColor(white);
	loadButtons();
	return 0;
}

int resetCanvas() {
	clearCanvas();
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
			DrawRectangle* drawrec = new DrawRectangle(dynamic_cast<Rectangle*>(sp.get()));
			dr->prepareToDraw(drawrec);
			dr->Draw();
		}
		else if(sp->getType() == "Circle") {
			Circle* c = dynamic_cast<Circle*>(sp.get());
			DrawCircle* drawrec = new DrawCircle(c);
			dr->prepareToDraw(drawrec);
			dr->Draw();
		}
	}
}

void deleteShape() {
	SDL_Log("DELETE CALLED, SHAPES SIZE %d", (int)shapes.size());
	for(int i = 0; i < shapes.size(); i++) {
		SDL_Log("Found a type %s on index %d that says selected: %d", shapes.at(i)->getType().c_str(), i, shapes.at(i)->getSelected());
		if(shapes.at(i)->getType() == "Rectangle") {
			if (shapes.at(i)->getSelected()){
				shapes.erase(shapes.begin() + i);
				break;
			}
		}
		else if(shapes.at(i)->getType() == "Circle") {
			if (shapes.at(i)->getSelected()) {
				shapes.erase(shapes.begin() + i);
				break;
			}
		}
	}
	SDL_Log("SHAPES SIZE %d AFTER DELETION", (int)shapes.size());
	clearCanvas();
	drawShapes();
}

void loadCanvas() {
	std::ifstream i(SAVE_PATH);
	json j;
	i >> j;
	std::cout << j;
	resetCanvas();
	SDL_Color c = {255, 255, 255};
	dr->setDrawingColor(c);
	for(int i = 0; i < (int)j.size(); ++i) {
		SDL_Log("j[%d]['type'] = %s", i, j[i]["type"].get<std::string>().c_str());
		if (j[i]["type"].get<std::string>() == "Rectangle") {
			Rectangle r = Rectangle(j[i]["width"].get<int>(), j[i]["height"].get<int>(), j[i]["posX"].get<int>(), j[i]["posY"].get<int>());
			shapes.push_back(std::make_unique<Rectangle>(r));
			DrawRectangle* drawrec = new DrawRectangle(&r);
			dr->prepareToDraw(drawrec);
			dr->Draw();
		}
		else if (j[i]["type"].get<std::string>() == "Circle") {
			Circle r = Circle(j[i]["width"].get<int>(), j[i]["height"].get<int>(), j[i]["posX"].get<int>() + (j[i]["width"].get<int>() / 2), j[i]["posY"].get<int>() + (j[i]["height"].get<int>() / 2));
			shapes.push_back(std::make_unique<Circle>(r));
			DrawCircle* drawcirc = new DrawCircle(&r);
			dr->prepareToDraw(drawcirc);
			dr->Draw();
		}
	}
	drawShapes();
	i.close();
}

bool checkIfButtonPressed(int mouseX, int mouseY) {
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
				deleteShape();
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
	if(mouseBeingHeld) {
		howLongBeingHeld++;
		SDL_Log("howLongBeingHeld: %d", howLongBeingHeld);
	}
	// Live preview of the Rectangle drawing
	if (mouseBeingHeld) {
		dr->updateMouseEnd(mouseBeingHeld);
		if(!checkIfButtonPressed(dr->getMouseEndX(), dr->getMouseEndY())) {
			switch(currentMode) {
				// Rectangle
				/*
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
						dr->prepareToDraw(drawrec);
						dr->Draw();
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
						dr->prepareToDraw(&drawcirc);
						dr->Draw();
					}
					break;
					*/
			}
		}
	}

	switch (event.type) {
	case SDL_QUIT:
	    Quit();
	    break;
	case SDL_MOUSEBUTTONUP:
		SDL_Log("MOUSEBUTTONUP!");
		mouseBeingHeld = false;
		if(currentMode == -1 && howLongBeingHeld > 1 && holdingRectangle != nullptr) {
			SDL_Log("holdingPosX: %d, holdingPosY: %d", holdingPosX, holdingPosY);
			holdingRectangle->setPosX(dr->getMouseX() - holdingPosX);
			holdingRectangle->setPosY(dr->getMouseY() - holdingPosY);
			DrawRectangle* drawrec = new DrawRectangle(holdingRectangle);
			dr->prepareToDraw(drawrec);
			dr->Draw();
			holdingRectangle = nullptr;
		}
		howLongBeingHeld = 0;
		dr->updateMouseEnd(mouseBeingHeld);
	    switch (event.button.button) {
	    case SDL_BUTTON_LEFT:
		if(!checkIfButtonPressed(dr->getMouseEndX(), dr->getMouseEndY())) {
			int mX = dr->getMouseX();
			int mY = dr->getMouseY();
			int mEndX = dr->getMouseEndX();
			int mEndY = dr->getMouseEndY();
			switch(currentMode) {
				// Rectangle
				case 1:
					{
						Rectangle rec = Rectangle(mEndX - mX, mEndY - mY, mX, mY);
						dynamicResize(&rec, dr->getMouseX(), dr->getMouseY(), dr->getMouseEndX(), dr->getMouseEndY());
						shapes.push_back(std::make_unique<Rectangle>(rec));
						DrawRectangle* drawrec = new DrawRectangle(&rec);
						dr->prepareToDraw(drawrec);
						dr->Draw();
						break;
					}
				// Ellipse
				case 2:
					{
						Circle circ = Circle(mEndX - mX, mEndY - mY, mX, mY);
						dynamicResize(&circ, dr->getMouseX(), dr->getMouseY(), dr->getMouseEndX(), dr->getMouseEndY());
						shapes.push_back(std::make_unique<Circle>(circ));
						DrawCircle drawcirc = DrawCircle(&circ);
						dr->prepareToDraw(&drawcirc);
						dr->Draw();
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
		dr->updateMouse(mouseBeingHeld);
		if(!checkIfButtonPressed(dr->getMouseX(), dr->getMouseY())) {
			switch(event.button.button) {
				case SDL_BUTTON_LEFT:
					{
						switch(currentMode) {
							case -1:
								{
								int mX = dr->getMouseX();
								int mY = dr->getMouseY();
								int shapes_size = shapes.size();
								if (shapes_size > 0) {
									for(int i = shapes_size - 1; i >= 0; i--) {
										auto& sp = shapes.at(i);
										sp->Deselect();
										if(sp->getType() == "Rectangle") {
											DrawRectangle* drawrec = new DrawRectangle(dynamic_cast<Rectangle*>(sp.get()));
											dr->prepareToDraw(drawrec);
											dr->Draw();
										}
										else if(sp->getType() == "Circle") {
											Circle* c = dynamic_cast<Circle*>(sp.get());
											DrawCircle* drawrec = new DrawCircle(c);
											dr->prepareToDraw(drawrec);
											dr->Draw();
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

											if(sp->getType() == "Rectangle") {
												DrawRectangle* drawrec = new DrawRectangle(dynamic_cast<Rectangle*>(sp.get()));
												dr->prepareToDraw(drawrec);
												dr->Draw();

												SDL_Log("Voordat ik de if ga checken is howLongBeingHeld nu op %d", howLongBeingHeld);
												if(howLongBeingHeld == 0) {
													dr->updateMouse(mouseBeingHeld);
													holdingPosX = dr->getMouseX() - sp->getPosX();
													holdingPosY = dr->getMouseY() - sp->getPosY();
													SDL_Log("holdingPosX: %d, holdingPosY: %d", holdingPosX, holdingPosY);
													holdingRectangle = dynamic_cast<Rectangle*>(sp.get());
												}
											}
											else if(sp->getType() == "Circle") {
												Circle* c = dynamic_cast<Circle*>(sp.get());
												DrawCircle* drawcirc = new DrawCircle(c);
												dr->prepareToDraw(drawcirc);
												dr->Draw();
											}
											break;
										}
									}
								}
								break;
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
