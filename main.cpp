#include "main.h"
#define BUTTON_WIDTH 75
#define BUTTON_HEIGHT 75
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
// Objects
TextureManager tm;
Drawer* dr;
Shape* selectedShape = nullptr;
vector<std::unique_ptr<Shape>> shapes;
// Fonts, initialized in Init()
// Debug
int updateCount = 0;

int loadButtons() {
	SDL_Log("Loading buttons");
	SDL_Color text = {255,255,255};

	// Button -1 - Select - Vertical
	SDL_Texture* button_tex = tm.getTextureByName("button");
	SDL_Texture* button_active = tm.getTextureByName("button-active");
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
	SDL_RenderCopy(gRenderer, button_tex, NULL, b_rect);
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

/* Shape* searchForShapeWithPos(int width, int height, int posX, int posY) { */
/* 	int shapeId = (width * 7) + (height * 7) + (posX * 7) + (posY * 7); */
/* 	for(Shape& s : shapes) { */
/* 		if(s.getId() == shapeId) { */
/* 			return &s; */
/* 		} */
/* 	} */
/* 	SDL_Log("ERROR: SHAPE NOT FOUND!"); */
/* 	return NULL; */
/* } */

int resetCanvas() {
	SDL_Log("resetCanvas() called");
	shapes.clear();
	currentMode = 0;
	SDL_Color color = {0, 0, 0};
	dr->setDrawingColor(color);
	SDL_RenderClear(gRenderer);
	loadButtons();
	return 0;
}

bool checkIfButtonPressed(int mouseX, int mouseY) {
	if(!mouseBeingHeld) {
		// Horizontal
		if(mouseY >= 0 && mouseY <= BUTTON_HEIGHT) {
		// Pressed first button - RESET
			if(mouseX >= 0 && mouseX <= BUTTON_WIDTH) {
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
			if(mouseY <= BUTTON_HEIGHT * 2) {
				currentMode = -1;
				loadButtons();
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
	updateCount++;
	if(updateCount % 200 == 0) {
		SDL_Log("Update: %s", std::to_string(updateCount).c_str());
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
		mouseBeingHeld = false;
		dr->updateMouseEnd(mouseBeingHeld);
	    switch (event.button.button) {
	    case SDL_BUTTON_LEFT:
		if(!checkIfButtonPressed(dr->getMouseEndX(), dr->getMouseEndY())) {
			switch(currentMode) {
				// Rectangle
				case 1:
					{
						int mX = dr->getMouseX();
						int mY = dr->getMouseY();
						int mEndX = dr->getMouseEndX();
						int mEndY = dr->getMouseEndY();
						Rectangle rec = Rectangle(mEndX - mX, mEndY - mY, mX, mY);
						shapes.push_back(std::make_unique<Rectangle>(rec));
						DrawRectangle* drawrec = new DrawRectangle(&rec);
						dr->prepareToDraw(drawrec);
						dr->Draw();
						break;
					}
				// Ellipse
				case 2:
					{
						dr->updateMouseEnd(mouseBeingHeld);
						int mX = dr->getMouseX();
						int mY = dr->getMouseY();
						int mEndX = dr->getMouseEndX();
						int mEndY = dr->getMouseEndY();
						Circle circ = Circle(mEndX - mX, mEndY - mY, mX, mY);
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
		switch(event.button.button) {
			case SDL_BUTTON_LEFT:
				{
					switch(currentMode) {
						case -1:
							{
							SDL_Log("EXECUTING SELECT");
							int mX = dr->getMouseX();
							SDL_Log("mouseX: %s", std::to_string(mX).c_str());
							int mY = dr->getMouseY();
							SDL_Log("mouseY: %s", std::to_string(mY).c_str());
							if (shapes.size() != 0) {
								for(int i = 0; i >= shapes.size(); i++) {
									shapes.at(i)->Deselect();
									if(shapes.at(i)->getType() == "Rectangle") {
										DrawRectangle* drawrec = new DrawRectangle(dynamic_cast<Rectangle*>(shapes.at(i).get()));
										dr->prepareToDraw(drawrec);
										dr->Draw();
									}
									else if(shapes.at(i)->getType() == "Circle") {
										DrawCircle* drawrec = new DrawCircle(dynamic_cast<Circle*>(shapes.at(i).get()));
										dr->prepareToDraw(drawrec);
										dr->Draw();
									}
								}
								SDL_Log("Going through for loop to search for shape, amount of shapes: %s", std::to_string(shapes.size()).c_str());
								bool haveSelectedAlready = false;
								for(int i = shapes.size() - 1; i >= 0; i--) {
									if (!haveSelectedAlready &&
										mX >= shapes.at(i)->getPosX() &&
										mX <= shapes.at(i)->getPosX() + shapes.at(i)->getWidth() &&
										mY >= shapes.at(i)->getPosY() &&
										mY <= shapes.at(i)->getPosY() + shapes.at(i)->getHeight()
										) {

										SDL_Log("SELECTED SHAPE at position %s!\n===\nType: %s\nWidth: %d\nHeight: %d\n===", std::to_string(i).c_str(), shapes.at(i)->getType().c_str(), shapes.at(i)->getWidth(), shapes.at(i)->getHeight());
										shapes.at(i)->Select();

										if(shapes.at(i)->getType() == "Rectangle") {
											DrawRectangle* drawrec = new DrawRectangle(dynamic_cast<Rectangle*>(shapes.at(i).get()));
											dr->prepareToDraw(drawrec);
											dr->Draw();
										}
										else if(shapes.at(i)->getType() == "Circle") {
											DrawCircle* drawcirc = new DrawCircle(dynamic_cast<Circle*>(shapes.at(i).get()));
											dr->prepareToDraw(drawcirc);
											dr->Draw();
										}
										haveSelectedAlready = true;
									}
									else {
										SDL_Log("DESELECTING SHAPE at position %s!\n===\nType: %s\nWidth: %d\nHeight: %d\nposX: %d\nposY: %d\n===", std::to_string(i).c_str(), shapes.at(i)->getType().c_str(), shapes.at(i)->getWidth(), shapes.at(i)->getHeight(), shapes.at(i)->getPosX(), shapes.at(i)->getPosY());
										shapes.at(i)->Deselect();
										if(shapes.at(i)->getType() == "Rectangle") {
											DrawRectangle* drawrec = new DrawRectangle(dynamic_cast<Rectangle*>(shapes.at(i).get()));
											dr->prepareToDraw(drawrec);
											dr->Draw();
										}
										else if(shapes.at(i)->getType() == "Circle") {
											DrawCircle* drawcirc = new DrawCircle(dynamic_cast<Circle*>(shapes.at(i).get()));
											dr->prepareToDraw(drawcirc);
											dr->Draw();
										}
									}
								}
							}
							break;
							}
					}
				}
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
