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

void DPDrawing::UndoHandler::Reset() {
	timesteps.clear();
	redotimesteps.clear();
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
void DPDrawing::UndoHandler::setShapes(vector<Shape*>& v) {
		for(int i = 0; i < (int)v.size(); ++i) {
			if (v.at(i)->getType() == "Rectangle") {
				Rectangle r = Rectangle(v.at(i)->getWidth(), v.at(i)->getHeight(), v.at(i)->getPosX(), v.at(i)->getPosY());
				shapes->push_back(std::make_unique<Rectangle>(r));
			}
			else if (v.at(i)->getType() == "Circle") {
				Circle r = Circle(v.at(i)->getWidth(), v.at(i)->getHeight(), v.at(i)->getPosX(), v.at(i)->getPosY());
				shapes->push_back(std::make_unique<Circle>(r));
			}
		}
}

void DPDrawing::UndoHandler::Redo() {
	if(!redotimesteps.empty()) {
		vector<Shape*> shapesInCurrentTimestep;
		shapesInCurrentTimestep = redotimesteps.back();
		redotimesteps.erase(redotimesteps.begin() + redotimesteps.size() - 1);
		setShapes(shapesInCurrentTimestep);
		Update(false);
	}
}

void DPDrawing::UndoHandler::Undo() {
	std::cout << "Before undo:" << std::endl;
	printTimesteps();
	if(!timesteps.empty()) {
		if(timesteps.size() == 1) {
			redotimesteps.push_back(timesteps.at(0));
			timesteps.clear();
		}
		else if(timesteps.size() >= 2) {
			vector<Shape*> shapesInCurrentTimestep;
			shapesInCurrentTimestep = timesteps.at((int)timesteps.size() - 2);
			redotimesteps.push_back(timesteps.back());
			timesteps.erase(timesteps.begin() + timesteps.size() - 1);
			setShapes(shapesInCurrentTimestep);
		}
	}
}
