#include "ButtonHandler.h"
DPDrawing::ButtonHandler::ButtonHandler(Invoker* inv, SDL_Renderer* renderer, TextureManager* tm, UndoHandler* uh, MouseHandler* mh, vector<unique_ptr<Shape>>* shapes, TTF_Font* font, int* currentMode, const int* BUTTON_WIDTH, const int* BUTTON_HEIGHT) { 
	this->inv = inv;
	this->renderer = renderer;
	this->tm = tm;
	this->uh = uh;
	this->mh = mh;
	this->shapes = shapes;
	this->font = font;
	this->currentMode = currentMode;
	this->BUTTON_WIDTH = BUTTON_WIDTH;
	this->BUTTON_HEIGHT = BUTTON_HEIGHT;
}

bool DPDrawing::ButtonHandler::checkIfButtonPressed(bool execute) {
	int mouseX = mh->getMouseX();
	int mouseY = mh->getMouseY();
		// Horizontal
		if(mouseY >= 0 && mouseY <= *BUTTON_HEIGHT) {
		// Pressed first button - RESET
			if(mouseX >= 0 && mouseX <= *BUTTON_WIDTH) {
				if(execute) {
					*currentMode = 0;
					HardResetCommand* resetc = new HardResetCommand(inv, uh, renderer, font, tm, shapes, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
					inv->addCommand(resetc);
					inv->Invoke();
					SDL_Log("0");
				}
				return true;
			}
			// Pressed second button - RECTANGLE
			else if(mouseX >= *BUTTON_WIDTH * 1 && mouseX <= *BUTTON_WIDTH * 2) {
				if(execute) {
					*currentMode = 1;
					LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
					inv->addCommand(lbc);
					inv->Invoke();
					SDL_Log("1");
				}
				return true;
			}
			// Pressed third button - ELLIPSE
			else if(mouseX >= *BUTTON_WIDTH * 2 && mouseX <= *BUTTON_WIDTH * 3) {
				if(execute) {
					*currentMode = 2;
					LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
					inv->addCommand(lbc);
					inv->Invoke();
					SDL_Log("2");
				}
				return true;
			}
		}
		// Vertical
		if(mouseX <= *BUTTON_WIDTH && mouseY >= 0) {
			// Select
			if(mouseY <= *BUTTON_HEIGHT * 2) {
				if(execute) {
					*currentMode = -1;
					LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
					inv->addCommand(lbc);
					inv->Invoke();
					SDL_Log("-1");
				}
				return true;
			}
			// Save
			else if(mouseY <= *BUTTON_HEIGHT * 3) {
				if(execute) {
					*currentMode = -2;
					SaveCommand* sc = new SaveCommand(shapes, "saves/saved.json");
					LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
					inv->addCommand(sc);
					inv->addCommand(lbc);
					inv->Invoke();
					SDL_Log("-2");
				}
				return true;
			}
			// Load
			else if(mouseY <= *BUTTON_HEIGHT * 4) {
				if(execute) {
					*currentMode = -3;
					ResetCommand* resetc = new ResetCommand(inv, renderer, font, tm, shapes, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
					LoadCommand* lc = new LoadCommand(shapes, "saves/saved.json", renderer);
					DrawShapesCommand* dsc = new DrawShapesCommand(inv, tm, shapes, renderer);
					inv->addCommand(resetc);
					inv->addCommand(lc);
					inv->addCommand(dsc);
					inv->Invoke();
					SDL_Log("-3");
				}
				return true;
			}
			// Delete Selected
			else if(mouseY <= *BUTTON_HEIGHT * 5) {
				if(execute) {
					*currentMode = -4;
					DeleteCommand* dc = new DeleteCommand(shapes);
					LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
					ClearCommand* clearc = new ClearCommand(inv, renderer, font, tm, shapes, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
					DrawShapesCommand* dsc = new DrawShapesCommand(inv, tm, shapes, renderer);
					inv->addCommand(dc);
					inv->addCommand(lbc);
					inv->addCommand(clearc);
					inv->addCommand(dsc);
					inv->Invoke();
					SDL_Log("-4");
				}
				return true;
			}
			// Resize
			else if(mouseY <= *BUTTON_HEIGHT * 6) {
				if(execute) {
					*currentMode = -5;
					LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
					inv->addCommand(lbc);
					inv->Invoke();
					SDL_Log("-5");
				}
				return true;
			}
			// Undo
			else if(mouseY <= *BUTTON_HEIGHT * 7) {
				if(execute) {
					*currentMode = -6;
					ResetCommand* resetc = new ResetCommand(inv, renderer, font, tm, shapes, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
					inv->addCommand(resetc);
					inv->Invoke();
					LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
					uh->Undo();
					DrawShapesCommand* dsc = new DrawShapesCommand(inv, tm, shapes, renderer);
					inv->addCommand(lbc);
					inv->addCommand(dsc);
					inv->Invoke();
					SDL_Log("-6");
				}
				return true;
			}
			// Redo
			else if(mouseY <= *BUTTON_HEIGHT * 8) {
				if(execute) {
					*currentMode = -7;
					ClearCommand* clearc = new ClearCommand(inv, renderer, font, tm, shapes, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
					inv->addCommand(clearc);
					uh->Redo();
					LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
					DrawShapesCommand* dsc = new DrawShapesCommand(inv, tm, shapes, renderer);
					inv->addCommand(lbc);
					inv->addCommand(dsc);
					inv->Invoke();
					SDL_Log("-7");
				}
				return true;
			}
			else {
				return false;
			}
		}
	return false;
}

