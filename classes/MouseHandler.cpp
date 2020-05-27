#include "MouseHandler.h"
DPDrawing::MouseHandler::MouseHandler() {
}

void DPDrawing::MouseHandler::Update() {
	if(mouseBeingHeld) {
		updateEndPos();
		howLongBeingHeld++;
	}
	else {
		updateBeginPos();
		howLongBeingHeld = 0;
	}
}

void DPDrawing::MouseHandler::updateMouseBeingHeld() {
	// Invert mouseBeingHeld boolean
	mouseBeingHeld ^= true;
}

void DPDrawing::MouseHandler::updateHoldingPos(int x, int y) {
	holdingPos.x = x;
	holdingPos.y = y;
}

void DPDrawing::MouseHandler::updateBeginPos() {
	SDL_GetMouseState(&beginPos.x, &beginPos.y);
}

void DPDrawing::MouseHandler::updateEndPos() {
	SDL_GetMouseState(&endPos.x, &endPos.y);
}

int DPDrawing::MouseHandler::getMouseX() {
	return beginPos.x;
}

int DPDrawing::MouseHandler::getMouseY() {
	return beginPos.y;
}

int DPDrawing::MouseHandler::getMouseEndX() {
	return endPos.x;
}

int DPDrawing::MouseHandler::getMouseEndY() {
	return endPos.y;
}

int DPDrawing::MouseHandler::getHoldingPosX() {
	return holdingPos.x;
}

int DPDrawing::MouseHandler::getHoldingPosY() {
	return holdingPos.y;
}

bool DPDrawing::MouseHandler::getMouseBeingHeld() {
	return mouseBeingHeld;
}

int DPDrawing::MouseHandler::getHowLongBeingHeld() {
	return howLongBeingHeld;
}
