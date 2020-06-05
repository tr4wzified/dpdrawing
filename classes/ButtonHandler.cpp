#include "ButtonHandler.h"
DPDrawing::ButtonHandler::ButtonHandler(MouseHandler* mh, int button_width, int button_height) {
	this->mh = mh;
}

bool DPDrawing::ButtonHandler::checkIfButtonPressed() {
	int mouseX = mh->getMouseX();
	int mouseY = mh->getMouseY();
	//if(!mouseBeingHeld) {
		// Horizontal
		if(mouseY >= 0 && mouseY <= button_height) {
		// Pressed first button - RESET
			if(mouseX >= 0 && mouseX <= button_width) {
				currentMode = 0;
				resetCanvas();
				return true;
			}
			// Pressed second button - RECTANGLE
			else if(mouseX >= button_width * 1 && mouseX <= button_width * 2) {
				currentMode = 1;
				loadButtons();
				return true;
			}
			// Pressed third button - ELLIPSE
			else if(mouseX >= button_width * 2 && mouseX <= button_width * 3) {
				currentMode = 2;
				loadButtons();
				return true;
			}
			return false;
		}
		// Vertical
		else if(mouseX <= button_width && mouseY >= 0) {
			// Select
			if(mouseY <= button_height * 2) {
				currentMode = -1;
				loadButtons();
				return true;
			}
			// Save
			else if(mouseY <= button_height * 3) {
				currentMode = -2;
				SaveCommand sc(&shapes, "saves/saved.json");
				inv->addCommand(&sc);
				inv->Invoke();
				loadButtons();
				return true;
			}
			// Load
			else if(mouseY <= button_height * 4) {
				currentMode = -3;
				resetCanvas();
				LoadCommand lc(&shapes, "saves/saved.json");
				inv->addCommand(&lc);
				inv->Invoke();
				drawShapes();
				return true;
			}
			// Delete Selected
			else if(mouseY <= button_height * 5) {
				currentMode = -4;
				loadButtons();
				DeleteCommand dc(&shapes);
				inv->addCommand(&dc);
				inv->Invoke();
				clearCanvas();
				drawShapes();
				return true;
			}
			else if(mouseY <= button_height * 6) {
				currentMode = -5;
				loadButtons();
				return true;
			}
		}
	return false;
}

