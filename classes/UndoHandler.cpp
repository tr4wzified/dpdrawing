#include "UndoHandler.h"
DPDrawing::UndoHandler::UndoHandler(SDL_Renderer* renderer, TTF_Font* font, TextureManager* tm, vector<unique_ptr<Shape>>* shapes, int* currentMode, const int* BUTTON_WIDTH, const int* BUTTON_HEIGHT) {
	this->renderer = renderer;
	this->font = font;
	this->tm = tm;
	this->shapes = shapes;
	this->currentMode = currentMode;
	this->BUTTON_WIDTH = BUTTON_WIDTH;
	this->BUTTON_HEIGHT = BUTTON_HEIGHT;
}

void DPDrawing::UndoHandler::Update(bool clearRedo) {
	SDL_Log("Updating timesteps");
	vector<Shape*> tempVec;
	for(int i = 0; i < (int)shapes->size(); i++) {
		if(shapes->at(i)->getType() == "Rectangle") {
			tempVec.push_back(new Rectangle(shapes->at(i)->getWidth(), shapes->at(i)->getHeight(), shapes->at(i)->getPosX(), shapes->at(i)->getPosY()));
		}
		else if(shapes->at(i)->getType() == "Circle") {
			tempVec.push_back(new Circle(shapes->at(i)->getWidth(), shapes->at(i)->getHeight(), shapes->at(i)->getPosX(), shapes->at(i)->getPosY()));
		}
	}
	if(clearRedo) {
		redotimesteps.clear();
	}
	timesteps.push_back(tempVec);
}

void DPDrawing::UndoHandler::printTimesteps() {
	for(int i = 0; i < (int)timesteps.size(); i++) {
		vector<Shape*> timestep = timesteps.at(i);
		cout << "Timestep " << i << ":" << std::endl;
		for(int j = 0; j < (int)timestep.size(); j++) {
			Shape* shape = timestep.at(j);
			cout << "	Shape number " << j << " is type " << shape->getType() << std::endl;
		}
	}
}

void DPDrawing::UndoHandler::printRedoTimesteps() {
	for(int i = 0; i < (int)redotimesteps.size(); i++) {
		vector<Shape*> redotimestep = redotimesteps.at(i);
		cout << "RedoTimestep " << i << ":" << std::endl;
		for(int j = 0; j < (int)redotimestep.size(); j++) {
			Shape* shape = redotimestep.at(j);
			cout << "	Shape number " << j << " is type " << shape->getType() << std::endl;
		}
	}
}

void DPDrawing::UndoHandler::Redo() {
	SDL_Log("Redo() called, timesteps size: %d, redotimesteps size: %d", (int)timesteps.size(), (int)redotimesteps.size());
	printTimesteps();
	printRedoTimesteps();
	if(!redotimesteps.empty()) {
		// Reset
		*currentMode = 0;
		shapes->clear();
		if(renderer == nullptr) {
			SDL_Log("ERROR: Renderer is NULLPTR!");
		}
		if(font == nullptr) {
			SDL_Log("ERROR: font is NULLPTR!");
		}
		if(tm == nullptr) {
			SDL_Log("ERROR: tm is NULLPTR!");
		}
		if(shapes == nullptr) {
			SDL_Log("ERROR: shapes is NULLPTR!");
		}
		if(currentMode == nullptr) {
			SDL_Log("ERROR: currentMode is NULLPTR!");
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_Texture* button_tex = tm->getTextureByName("button");
		SDL_Texture* button_active = tm->getTextureByName("button-active");

		if(button_tex == nullptr) {
			SDL_Log("ERROR: button is nullptr in LoadButtonsCommand");
		}
		if(button_active == nullptr) {
			SDL_Log("ERROR: button-active is nullptr in LoadButtonsCommand");
		}

		SDL_Color text = {255,255,255};

		// Button -6 - Redo - Vertical
		Button u(0, *BUTTON_HEIGHT * 7, text, 62, font);
		SDL_Rect* u_rect = u.getRectangle();
		SDL_Texture* u_msg = SDL_CreateTextureFromSurface(renderer, u.getSurface());
		SDL_Rect* u_msg_rect = u.getRectangle();
		if(*currentMode == -7) {
			SDL_RenderCopy(renderer, button_active, NULL, u_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, u_rect);
		}
		SDL_RenderCopy(renderer, u_msg, NULL, u_msg_rect);

		// Button -6 - Undo - Vertical
		Button v(0, *BUTTON_HEIGHT * 6, text, 60, font);
		SDL_Rect* v_rect = v.getRectangle();
		SDL_Texture* v_msg = SDL_CreateTextureFromSurface(renderer, v.getSurface());
		SDL_Rect* v_msg_rect = v.getRectangle();
		if(*currentMode == -6) {
			SDL_RenderCopy(renderer, button_active, NULL, v_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, v_rect);
		}
		SDL_RenderCopy(renderer, v_msg, NULL, v_msg_rect);

		// Button -5 - Resize - Vertical
		Button w(0, *BUTTON_HEIGHT * 5, text, 124, font);
		SDL_Rect* w_rect = w.getRectangle();
		SDL_Texture* w_msg = SDL_CreateTextureFromSurface(renderer, w.getSurface());
		SDL_Rect* w_msg_rect = w.getRectangle();
		if(*currentMode == -5) {
			SDL_RenderCopy(renderer, button_active, NULL, w_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, w_rect);
		}
		SDL_RenderCopy(renderer, w_msg, NULL, w_msg_rect);

		// Button -4 - Delete - Vertical
		Button x(0, *BUTTON_HEIGHT * 4, text, 68, font);
		SDL_Rect* x_rect = x.getRectangle();
		SDL_Texture* x_msg = SDL_CreateTextureFromSurface(renderer, x.getSurface());
		SDL_Rect* x_msg_rect = x.getRectangle();
		if(*currentMode == -4) {
			SDL_RenderCopy(renderer, button_active, NULL, x_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, x_rect);
		}
		SDL_RenderCopy(renderer, x_msg, NULL, x_msg_rect);

		// Button -3 - JSON Load - Vertical
		Button y(0, *BUTTON_HEIGHT * 3, text, 76, font);
		SDL_Rect* y_rect = y.getRectangle();
		SDL_Texture* y_msg = SDL_CreateTextureFromSurface(renderer, y.getSurface());
		SDL_Rect* y_msg_rect = y.getRectangle();
		if(*currentMode == -3) {
			SDL_RenderCopy(renderer, button_active, NULL, y_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, y_rect);
		}
		SDL_RenderCopy(renderer, y_msg, NULL, y_msg_rect);

		// Button -2 - JSON Save - Vertical
		Button z(0, *BUTTON_HEIGHT * 2, text, 74, font);
		SDL_Rect* z_rect = z.getRectangle();
		SDL_Texture* z_msg = SDL_CreateTextureFromSurface(renderer, z.getSurface());
		SDL_Rect* z_msg_rect = z.getRectangle();
		if(*currentMode == -2) {
			SDL_RenderCopy(renderer, button_active, NULL, z_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, z_rect);
		}
		SDL_RenderCopy(renderer, z_msg, NULL, z_msg_rect);

		// Button -1 - Select - Vertical
		Button a(0, *BUTTON_HEIGHT, text, 83, font);
		SDL_Rect* a_rect = a.getRectangle();
		SDL_Texture* a_msg = SDL_CreateTextureFromSurface(renderer, a.getSurface());
		SDL_Rect* a_msg_rect = a.getRectangle();
		if(*currentMode == -1) {
			SDL_RenderCopy(renderer, button_active, NULL, a_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, a_rect);
		}
		SDL_RenderCopy(renderer, a_msg, NULL, a_msg_rect);

		// Button 1 - Reset
		Button b(0, 0, text, 88, font);
		SDL_Rect* b_rect = b.getRectangle();
		SDL_Texture* b_msg = SDL_CreateTextureFromSurface(renderer, b.getSurface());
		SDL_Rect* b_msg_rect = b.getRectangle();
		if(currentMode == 0) {
			SDL_RenderCopy(renderer, button_active, NULL, b_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, b_rect);
		}
		SDL_RenderCopy(renderer, b_msg, NULL, b_msg_rect);

		// Button 2 - Rectangle - R
		Button c(*BUTTON_WIDTH, 0, text, 82, font);
		SDL_Rect* c_rect = c.getRectangle();
		SDL_Texture* c_msg = SDL_CreateTextureFromSurface(renderer, c.getSurface());
		SDL_Rect* c_msg_rect = c.getRectangle();
		if(*currentMode == 1) {
			SDL_RenderCopy(renderer, button_active, NULL, c_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, c_rect);
		}
		SDL_RenderCopy(renderer, c_msg, NULL, c_msg_rect);

		// Button 3 - Ellipse - O
		Button d(*BUTTON_WIDTH * 2, 0, text, 79, font);
		SDL_Rect* d_rect = d.getRectangle();
		SDL_Texture* d_msg = SDL_CreateTextureFromSurface(renderer, d.getSurface());
		SDL_Rect* d_msg_rect = d.getRectangle();
		if(*currentMode == 2) {
			SDL_RenderCopy(renderer, button_active, NULL, d_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, d_rect);
		}
		SDL_RenderCopy(renderer, d_msg, NULL, d_msg_rect);

		SDL_RenderPresent(renderer);

		// Destroy
		SDL_DestroyTexture(u_msg);
		SDL_DestroyTexture(v_msg);
		SDL_DestroyTexture(w_msg);
		SDL_DestroyTexture(x_msg);
		SDL_DestroyTexture(y_msg);
		SDL_DestroyTexture(z_msg);
		SDL_DestroyTexture(a_msg);
		SDL_DestroyTexture(b_msg);
		SDL_DestroyTexture(c_msg);
		SDL_DestroyTexture(d_msg);
		// end reset
		// get state to go towards
		vector<Shape*> shapesInCurrentTimestep;
		shapesInCurrentTimestep = redotimesteps.back();
		// push into undo?
		redotimesteps.erase(redotimesteps.begin() + redotimesteps.size() - 1);
		for(int i = 0; i < (int)shapesInCurrentTimestep.size(); ++i) {
			if (shapesInCurrentTimestep.at(i)->getType() == "Rectangle") {
				Rectangle r = Rectangle(shapesInCurrentTimestep.at(i)->getWidth(), shapesInCurrentTimestep.at(i)->getHeight(), shapesInCurrentTimestep.at(i)->getPosX(), shapesInCurrentTimestep.at(i)->getPosY());
				shapes->push_back(std::make_unique<Rectangle>(r));
			}
			else if (shapesInCurrentTimestep.at(i)->getType() == "Circle") {
				Circle r = Circle(shapesInCurrentTimestep.at(i)->getWidth(), shapesInCurrentTimestep.at(i)->getHeight(), shapesInCurrentTimestep.at(i)->getPosX(), shapesInCurrentTimestep.at(i)->getPosY());
				shapes->push_back(std::make_unique<Circle>(r));
			}
		}
		Update(false);
		for(int i = shapes->size() - 1; i >= 0; i--) {
			auto& sp = shapes->at(i);
			sp->Deselect();
			if(sp->getType() == "Rectangle") {
				Rectangle* mRect = dynamic_cast<Rectangle*>(sp.get());
				SDL_Rect* obj = mRect->getSDLObj();
				SDL_Texture* tex = (mRect->isSelected()) ? tm->getTextureByName("red") : tm->getTextureByName("white");
				SDL_RenderCopy(renderer, tex, NULL, obj);
				SDL_RenderPresent(renderer);
			}
			else if(sp->getType() == "Circle") {
				Circle* mCirc = dynamic_cast<Circle*>(sp.get());
				if (sp->isSelected()) {
					// Draw in red
					filledEllipseRGBA(renderer, mCirc->getPosX() + (mCirc->getWidth() / 2), mCirc->getPosY() + (mCirc->getHeight() / 2), mCirc->getWidth() / 2, mCirc->getHeight() / 2, (Uint8)255, (Uint8)0, (Uint8)0, (Uint8)255);
				}
				else {
					// Draw in white
					filledEllipseRGBA(renderer, mCirc->getPosX() + (mCirc->getWidth() / 2), mCirc->getPosY() + (mCirc->getHeight() / 2), mCirc->getWidth() / 2, mCirc->getHeight() / 2, (Uint8)255, (Uint8)255, (Uint8)255, (Uint8)255);
				}
				SDL_RenderPresent(renderer);
			}
		}
	}
}

void DPDrawing::UndoHandler::Undo() {
	SDL_Log("Undo() called, timesteps size: %d, redotimesteps size: %d", (int)timesteps.size(), (int)redotimesteps.size());
	printTimesteps();
	if(!timesteps.empty()) {
	if(timesteps.size() == 1) {
		timesteps.clear();
		// Reset
		*currentMode = 0;
		shapes->clear();
		if(renderer == nullptr) {
			SDL_Log("ERROR: Renderer is NULLPTR!");
		}
		if(font == nullptr) {
			SDL_Log("ERROR: font is NULLPTR!");
		}
		if(tm == nullptr) {
			SDL_Log("ERROR: tm is NULLPTR!");
		}
		if(shapes == nullptr) {
			SDL_Log("ERROR: shapes is NULLPTR!");
		}
		if(currentMode == nullptr) {
			SDL_Log("ERROR: currentMode is NULLPTR!");
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_Texture* button_tex = tm->getTextureByName("button");
		SDL_Texture* button_active = tm->getTextureByName("button-active");

		if(button_tex == nullptr) {
			SDL_Log("ERROR: button is nullptr in LoadButtonsCommand");
		}
		if(button_active == nullptr) {
			SDL_Log("ERROR: button-active is nullptr in LoadButtonsCommand");
		}

		SDL_Color text = {255,255,255};

		// Button -6 - Redo - Vertical
		Button u(0, *BUTTON_HEIGHT * 7, text, 62, font);
		SDL_Rect* u_rect = u.getRectangle();
		SDL_Texture* u_msg = SDL_CreateTextureFromSurface(renderer, u.getSurface());
		SDL_Rect* u_msg_rect = u.getRectangle();
		if(*currentMode == -7) {
			SDL_RenderCopy(renderer, button_active, NULL, u_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, u_rect);
		}
		SDL_RenderCopy(renderer, u_msg, NULL, u_msg_rect);

		// Button -6 - Undo - Vertical
		Button v(0, *BUTTON_HEIGHT * 6, text, 60, font);
		SDL_Rect* v_rect = v.getRectangle();
		SDL_Texture* v_msg = SDL_CreateTextureFromSurface(renderer, v.getSurface());
		SDL_Rect* v_msg_rect = v.getRectangle();
		if(*currentMode == -6) {
			SDL_RenderCopy(renderer, button_active, NULL, v_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, v_rect);
		}
		SDL_RenderCopy(renderer, v_msg, NULL, v_msg_rect);

		// Button -5 - Resize - Vertical
		Button w(0, *BUTTON_HEIGHT * 5, text, 124, font);
		SDL_Rect* w_rect = w.getRectangle();
		SDL_Texture* w_msg = SDL_CreateTextureFromSurface(renderer, w.getSurface());
		SDL_Rect* w_msg_rect = w.getRectangle();
		if(*currentMode == -5) {
			SDL_RenderCopy(renderer, button_active, NULL, w_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, w_rect);
		}
		SDL_RenderCopy(renderer, w_msg, NULL, w_msg_rect);

		// Button -4 - Delete - Vertical
		Button x(0, *BUTTON_HEIGHT * 4, text, 68, font);
		SDL_Rect* x_rect = x.getRectangle();
		SDL_Texture* x_msg = SDL_CreateTextureFromSurface(renderer, x.getSurface());
		SDL_Rect* x_msg_rect = x.getRectangle();
		if(*currentMode == -4) {
			SDL_RenderCopy(renderer, button_active, NULL, x_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, x_rect);
		}
		SDL_RenderCopy(renderer, x_msg, NULL, x_msg_rect);

		// Button -3 - JSON Load - Vertical
		Button y(0, *BUTTON_HEIGHT * 3, text, 76, font);
		SDL_Rect* y_rect = y.getRectangle();
		SDL_Texture* y_msg = SDL_CreateTextureFromSurface(renderer, y.getSurface());
		SDL_Rect* y_msg_rect = y.getRectangle();
		if(*currentMode == -3) {
			SDL_RenderCopy(renderer, button_active, NULL, y_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, y_rect);
		}
		SDL_RenderCopy(renderer, y_msg, NULL, y_msg_rect);

		// Button -2 - JSON Save - Vertical
		Button z(0, *BUTTON_HEIGHT * 2, text, 74, font);
		SDL_Rect* z_rect = z.getRectangle();
		SDL_Texture* z_msg = SDL_CreateTextureFromSurface(renderer, z.getSurface());
		SDL_Rect* z_msg_rect = z.getRectangle();
		if(*currentMode == -2) {
			SDL_RenderCopy(renderer, button_active, NULL, z_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, z_rect);
		}
		SDL_RenderCopy(renderer, z_msg, NULL, z_msg_rect);

		// Button -1 - Select - Vertical
		Button a(0, *BUTTON_HEIGHT, text, 83, font);
		SDL_Rect* a_rect = a.getRectangle();
		SDL_Texture* a_msg = SDL_CreateTextureFromSurface(renderer, a.getSurface());
		SDL_Rect* a_msg_rect = a.getRectangle();
		if(*currentMode == -1) {
			SDL_RenderCopy(renderer, button_active, NULL, a_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, a_rect);
		}
		SDL_RenderCopy(renderer, a_msg, NULL, a_msg_rect);

		// Button 1 - Reset
		Button b(0, 0, text, 88, font);
		SDL_Rect* b_rect = b.getRectangle();
		SDL_Texture* b_msg = SDL_CreateTextureFromSurface(renderer, b.getSurface());
		SDL_Rect* b_msg_rect = b.getRectangle();
		if(currentMode == 0) {
			SDL_RenderCopy(renderer, button_active, NULL, b_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, b_rect);
		}
		SDL_RenderCopy(renderer, b_msg, NULL, b_msg_rect);

		// Button 2 - Rectangle - R
		Button c(*BUTTON_WIDTH, 0, text, 82, font);
		SDL_Rect* c_rect = c.getRectangle();
		SDL_Texture* c_msg = SDL_CreateTextureFromSurface(renderer, c.getSurface());
		SDL_Rect* c_msg_rect = c.getRectangle();
		if(*currentMode == 1) {
			SDL_RenderCopy(renderer, button_active, NULL, c_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, c_rect);
		}
		SDL_RenderCopy(renderer, c_msg, NULL, c_msg_rect);

		// Button 3 - Ellipse - O
		Button d(*BUTTON_WIDTH * 2, 0, text, 79, font);
		SDL_Rect* d_rect = d.getRectangle();
		SDL_Texture* d_msg = SDL_CreateTextureFromSurface(renderer, d.getSurface());
		SDL_Rect* d_msg_rect = d.getRectangle();
		if(*currentMode == 2) {
			SDL_RenderCopy(renderer, button_active, NULL, d_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, d_rect);
		}
		SDL_RenderCopy(renderer, d_msg, NULL, d_msg_rect);

		SDL_RenderPresent(renderer);

		// Destroy
		SDL_DestroyTexture(u_msg);
		SDL_DestroyTexture(v_msg);
		SDL_DestroyTexture(w_msg);
		SDL_DestroyTexture(x_msg);
		SDL_DestroyTexture(y_msg);
		SDL_DestroyTexture(z_msg);
		SDL_DestroyTexture(a_msg);
		SDL_DestroyTexture(b_msg);
		SDL_DestroyTexture(c_msg);
		SDL_DestroyTexture(d_msg);
	}
	else if(timesteps.size() >= 2) {
		// Reset
		*currentMode = 0;
		shapes->clear();
		if(renderer == nullptr) {
			SDL_Log("ERROR: Renderer is NULLPTR!");
		}
		if(font == nullptr) {
			SDL_Log("ERROR: font is NULLPTR!");
		}
		if(tm == nullptr) {
			SDL_Log("ERROR: tm is NULLPTR!");
		}
		if(shapes == nullptr) {
			SDL_Log("ERROR: shapes is NULLPTR!");
		}
		if(currentMode == nullptr) {
			SDL_Log("ERROR: currentMode is NULLPTR!");
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_Texture* button_tex = tm->getTextureByName("button");
		SDL_Texture* button_active = tm->getTextureByName("button-active");

		if(button_tex == nullptr) {
			SDL_Log("ERROR: button is nullptr in LoadButtonsCommand");
		}
		if(button_active == nullptr) {
			SDL_Log("ERROR: button-active is nullptr in LoadButtonsCommand");
		}

		SDL_Color text = {255,255,255};

		// Button -6 - Redo - Vertical
		Button u(0, *BUTTON_HEIGHT * 7, text, 62, font);
		SDL_Rect* u_rect = u.getRectangle();
		SDL_Texture* u_msg = SDL_CreateTextureFromSurface(renderer, u.getSurface());
		SDL_Rect* u_msg_rect = u.getRectangle();
		if(*currentMode == -7) {
			SDL_RenderCopy(renderer, button_active, NULL, u_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, u_rect);
		}
		SDL_RenderCopy(renderer, u_msg, NULL, u_msg_rect);

		// Button -6 - Undo - Vertical
		Button v(0, *BUTTON_HEIGHT * 6, text, 60, font);
		SDL_Rect* v_rect = v.getRectangle();
		SDL_Texture* v_msg = SDL_CreateTextureFromSurface(renderer, v.getSurface());
		SDL_Rect* v_msg_rect = v.getRectangle();
		if(*currentMode == -6) {
			SDL_RenderCopy(renderer, button_active, NULL, v_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, v_rect);
		}
		SDL_RenderCopy(renderer, v_msg, NULL, v_msg_rect);

		// Button -5 - Resize - Vertical
		Button w(0, *BUTTON_HEIGHT * 5, text, 124, font);
		SDL_Rect* w_rect = w.getRectangle();
		SDL_Texture* w_msg = SDL_CreateTextureFromSurface(renderer, w.getSurface());
		SDL_Rect* w_msg_rect = w.getRectangle();
		if(*currentMode == -5) {
			SDL_RenderCopy(renderer, button_active, NULL, w_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, w_rect);
		}
		SDL_RenderCopy(renderer, w_msg, NULL, w_msg_rect);

		// Button -4 - Delete - Vertical
		Button x(0, *BUTTON_HEIGHT * 4, text, 68, font);
		SDL_Rect* x_rect = x.getRectangle();
		SDL_Texture* x_msg = SDL_CreateTextureFromSurface(renderer, x.getSurface());
		SDL_Rect* x_msg_rect = x.getRectangle();
		if(*currentMode == -4) {
			SDL_RenderCopy(renderer, button_active, NULL, x_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, x_rect);
		}
		SDL_RenderCopy(renderer, x_msg, NULL, x_msg_rect);

		// Button -3 - JSON Load - Vertical
		Button y(0, *BUTTON_HEIGHT * 3, text, 76, font);
		SDL_Rect* y_rect = y.getRectangle();
		SDL_Texture* y_msg = SDL_CreateTextureFromSurface(renderer, y.getSurface());
		SDL_Rect* y_msg_rect = y.getRectangle();
		if(*currentMode == -3) {
			SDL_RenderCopy(renderer, button_active, NULL, y_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, y_rect);
		}
		SDL_RenderCopy(renderer, y_msg, NULL, y_msg_rect);

		// Button -2 - JSON Save - Vertical
		Button z(0, *BUTTON_HEIGHT * 2, text, 74, font);
		SDL_Rect* z_rect = z.getRectangle();
		SDL_Texture* z_msg = SDL_CreateTextureFromSurface(renderer, z.getSurface());
		SDL_Rect* z_msg_rect = z.getRectangle();
		if(*currentMode == -2) {
			SDL_RenderCopy(renderer, button_active, NULL, z_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, z_rect);
		}
		SDL_RenderCopy(renderer, z_msg, NULL, z_msg_rect);

		// Button -1 - Select - Vertical
		Button a(0, *BUTTON_HEIGHT, text, 83, font);
		SDL_Rect* a_rect = a.getRectangle();
		SDL_Texture* a_msg = SDL_CreateTextureFromSurface(renderer, a.getSurface());
		SDL_Rect* a_msg_rect = a.getRectangle();
		if(*currentMode == -1) {
			SDL_RenderCopy(renderer, button_active, NULL, a_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, a_rect);
		}
		SDL_RenderCopy(renderer, a_msg, NULL, a_msg_rect);

		// Button 1 - Reset
		Button b(0, 0, text, 88, font);
		SDL_Rect* b_rect = b.getRectangle();
		SDL_Texture* b_msg = SDL_CreateTextureFromSurface(renderer, b.getSurface());
		SDL_Rect* b_msg_rect = b.getRectangle();
		if(currentMode == 0) {
			SDL_RenderCopy(renderer, button_active, NULL, b_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, b_rect);
		}
		SDL_RenderCopy(renderer, b_msg, NULL, b_msg_rect);

		// Button 2 - Rectangle - R
		Button c(*BUTTON_WIDTH, 0, text, 82, font);
		SDL_Rect* c_rect = c.getRectangle();
		SDL_Texture* c_msg = SDL_CreateTextureFromSurface(renderer, c.getSurface());
		SDL_Rect* c_msg_rect = c.getRectangle();
		if(*currentMode == 1) {
			SDL_RenderCopy(renderer, button_active, NULL, c_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, c_rect);
		}
		SDL_RenderCopy(renderer, c_msg, NULL, c_msg_rect);

		// Button 3 - Ellipse - O
		Button d(*BUTTON_WIDTH * 2, 0, text, 79, font);
		SDL_Rect* d_rect = d.getRectangle();
		SDL_Texture* d_msg = SDL_CreateTextureFromSurface(renderer, d.getSurface());
		SDL_Rect* d_msg_rect = d.getRectangle();
		if(*currentMode == 2) {
			SDL_RenderCopy(renderer, button_active, NULL, d_rect);
		}
		else {
			SDL_RenderCopy(renderer, button_tex, NULL, d_rect);
		}
		SDL_RenderCopy(renderer, d_msg, NULL, d_msg_rect);

		SDL_RenderPresent(renderer);

		// Destroy
		SDL_DestroyTexture(u_msg);
		SDL_DestroyTexture(v_msg);
		SDL_DestroyTexture(w_msg);
		SDL_DestroyTexture(x_msg);
		SDL_DestroyTexture(y_msg);
		SDL_DestroyTexture(z_msg);
		SDL_DestroyTexture(a_msg);
		SDL_DestroyTexture(b_msg);
		SDL_DestroyTexture(c_msg);
		SDL_DestroyTexture(d_msg);
		// end reset
		// get state to go towards
		vector<Shape*> shapesInCurrentTimestep;
		shapesInCurrentTimestep = timesteps.at((int)timesteps.size() - 2);
		redotimesteps.push_back(timesteps.back());
		timesteps.erase(timesteps.begin() + timesteps.size() - 1);
		for(int i = 0; i < (int)shapesInCurrentTimestep.size(); ++i) {
			if (shapesInCurrentTimestep.at(i)->getType() == "Rectangle") {
				Rectangle r = Rectangle(shapesInCurrentTimestep.at(i)->getWidth(), shapesInCurrentTimestep.at(i)->getHeight(), shapesInCurrentTimestep.at(i)->getPosX(), shapesInCurrentTimestep.at(i)->getPosY());
				shapes->push_back(std::make_unique<Rectangle>(r));
			}
			else if (shapesInCurrentTimestep.at(i)->getType() == "Circle") {
				Circle r = Circle(shapesInCurrentTimestep.at(i)->getWidth(), shapesInCurrentTimestep.at(i)->getHeight(), shapesInCurrentTimestep.at(i)->getPosX(), shapesInCurrentTimestep.at(i)->getPosY());
				shapes->push_back(std::make_unique<Circle>(r));
			}
		}
		for(int i = shapes->size() - 1; i >= 0; i--) {
			auto& sp = shapes->at(i);
			sp->Deselect();
			if(sp->getType() == "Rectangle") {
				Rectangle* mRect = dynamic_cast<Rectangle*>(sp.get());
				SDL_Rect* obj = mRect->getSDLObj();
				SDL_Texture* tex = (mRect->isSelected()) ? tm->getTextureByName("red") : tm->getTextureByName("white");
				SDL_RenderCopy(renderer, tex, NULL, obj);
				SDL_RenderPresent(renderer);
			}
			else if(sp->getType() == "Circle") {
				Circle* mCirc = dynamic_cast<Circle*>(sp.get());
				if (sp->isSelected()) {
					// Draw in red
					filledEllipseRGBA(renderer, mCirc->getPosX() + (mCirc->getWidth() / 2), mCirc->getPosY() + (mCirc->getHeight() / 2), mCirc->getWidth() / 2, mCirc->getHeight() / 2, (Uint8)255, (Uint8)0, (Uint8)0, (Uint8)255);
				}
				else {
					// Draw in white
					filledEllipseRGBA(renderer, mCirc->getPosX() + (mCirc->getWidth() / 2), mCirc->getPosY() + (mCirc->getHeight() / 2), mCirc->getWidth() / 2, mCirc->getHeight() / 2, (Uint8)255, (Uint8)255, (Uint8)255, (Uint8)255);
				}
				SDL_RenderPresent(renderer);
			}
		}
	}
	}
}
