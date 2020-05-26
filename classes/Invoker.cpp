#include "Invoker.h"
DPDrawing::Invoker::Invoker(SDL_Renderer* renderer, TextureManager* tm) {
	this->renderer = renderer;
	this->tm = tm;
};
void DPDrawing::Invoker::setDrawingColor(SDL_Color& c) {
	this->drawingColor = c;
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
}
void DPDrawing::Invoker::prepareToDraw(DrawCommand* cmd) {
	mCmds.push_back(cmd);
}
void DPDrawing::Invoker::updateMouse(bool mouseBeingHeld) {
	SDL_GetMouseState(&mouseX, &mouseY);
	this->mouseBeingHeld = mouseBeingHeld;
}
void DPDrawing::Invoker::updateMouseEnd(bool mouseBeingHeld) {
	SDL_GetMouseState(&mouseEndX, &mouseEndY);
	this->mouseBeingHeld = mouseBeingHeld;
}
int DPDrawing::Invoker::getMouseX() {
	return mouseX;
}
int DPDrawing::Invoker::getMouseY() {
	return mouseY;
}
int DPDrawing::Invoker::getMouseEndX() {
	return mouseEndX;
}
int DPDrawing::Invoker::getMouseEndY() {
	return mouseEndY;
}
void DPDrawing::Invoker::Draw() {
	for(DrawCommand* mCmd : mCmds) {
		if(mCmd == nullptr) {
			SDL_Log("ERROR: Calling Draw() on a nullptr! Your DrawCommand* likely went out of scope.");
		}
		mCmd->execute(renderer, tm);
	}
	SDL_RenderPresent(renderer);
	mCmds.clear();
} 
