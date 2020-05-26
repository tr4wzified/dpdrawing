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
	if(mouseBeingHeld) {
		mouseBeingHeld = false;
	}
	else {
		mouseBeingHeld = true;
	}
}

void DPDrawing::MouseHandler::updateBeginPos() {
	SDL_GetMouseState(&beginPos.x, &beginPos.y);
}

void DPDrawing::MouseHandler::updateEndPos() {
	SDL_GetMouseState(&endPos.x, &endPos.y);
}

int DPDrawing::MouseHandler::getBeginPosX() {
	return beginPos.x;
}

int DPDrawing::MouseHandler::getBeginPosY() {
	return beginPos.x;
}

int DPDrawing::MouseHandler::getEndPosX() {
	return endPos.x;
}

int DPDrawing::MouseHandler::getEndPosY() {
	return endPos.y;
}
