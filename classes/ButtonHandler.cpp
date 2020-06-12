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

bool DPDrawing::ButtonHandler::checkIfButtonPressed() {
	int mouseX = mh->getMouseX();
	int mouseY = mh->getMouseY();
	if(!mh->getMouseBeingHeld()) {
		// Horizontal
		if(mouseY >= 0 && mouseY <= *BUTTON_HEIGHT) {
		// Pressed first button - RESET
			if(mouseX >= 0 && mouseX <= *BUTTON_WIDTH) {
				*currentMode = 0;
				HardResetCommand* resetc = new HardResetCommand(inv, renderer, font, tm, shapes, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
				inv->addCommand(resetc);
				inv->Invoke();
				return true;
			}
			// Pressed second button - RECTANGLE
			else if(mouseX >= *BUTTON_WIDTH * 1 && mouseX <= *BUTTON_WIDTH * 2) {
				*currentMode = 1;
				LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
				inv->addCommand(lbc);
				inv->Invoke();
				return true;
			}
			// Pressed third button - ELLIPSE
			else if(mouseX >= *BUTTON_WIDTH * 2 && mouseX <= *BUTTON_WIDTH * 3) {
				*currentMode = 2;
				LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
				inv->addCommand(lbc);
				inv->Invoke();
				return true;
			}
			return false;
		}
		// Vertical
		else if(mouseX <= *BUTTON_WIDTH && mouseY >= 0) {
			// Select
			if(mouseY <= *BUTTON_HEIGHT * 2) {
				*currentMode = -1;
				LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
				inv->addCommand(lbc);
				inv->Invoke();
				return true;
			}
			// Save
			else if(mouseY <= *BUTTON_HEIGHT * 3) {
				*currentMode = -2;
				SaveCommand* sc = new SaveCommand(shapes, "saves/saved.json");
				LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
				inv->addCommand(sc);
				inv->addCommand(lbc);
				inv->Invoke();
				return true;
			}
			// Load
			else if(mouseY <= *BUTTON_HEIGHT * 4) {
				*currentMode = -3;
				ResetCommand* resetc = new ResetCommand(inv, renderer, font, tm, shapes, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
				LoadCommand* lc = new LoadCommand(shapes, "saves/saved.json", renderer);
				DrawShapesCommand* dsc = new DrawShapesCommand(inv, tm, shapes, renderer);
				inv->addCommand(resetc);
				inv->addCommand(lc);
				inv->addCommand(dsc);
				inv->Invoke();
				return true;
			}
			// Delete Selected
			else if(mouseY <= *BUTTON_HEIGHT * 5) {
				*currentMode = -4;
				LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
				DeleteCommand* dc = new DeleteCommand(shapes);
				ClearCommand* clearc = new ClearCommand(inv, renderer, font, tm, shapes, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
				DrawShapesCommand* dsc = new DrawShapesCommand(inv, tm, shapes, renderer);
				inv->addCommand(lbc);
				inv->addCommand(dc);
				inv->addCommand(clearc);
				inv->addCommand(dsc);
				inv->Invoke();
				return true;
			}
			// Resize
			else if(mouseY <= *BUTTON_HEIGHT * 6) {
				*currentMode = -5;
				LoadButtonsCommand* lbc = new LoadButtonsCommand(renderer, font, tm, currentMode, BUTTON_WIDTH, BUTTON_HEIGHT);
				inv->addCommand(lbc);
				inv->Invoke();
				return true;
			}
			// Undo
			else if(mouseY <= *BUTTON_HEIGHT * 7) {
				*currentMode = -6;
				DrawShapesCommand* dsc = new DrawShapesCommand(inv, tm, shapes, renderer);
				uh->Undo();
				inv->addCommand(dsc);
				inv->Invoke();
				return true;
			}
			// Redo
			else if(mouseY <= *BUTTON_HEIGHT * 8) {
				*currentMode = -7;
				DrawShapesCommand* dsc = new DrawShapesCommand(inv, tm, shapes, renderer);
				uh->Redo();
				inv->addCommand(dsc);
				inv->Invoke();
				return true;
			}
		}
	}
	return false;
}

