#include "Invoker.h"
DPDrawing::Invoker::Invoker(SDL_Renderer* renderer) {
	this->renderer = renderer;
};

void DPDrawing::Invoker::addCommand(Command* cmd) {
	if(cmd == nullptr) {
		SDL_Log("WARNING! Adding a NULLPTR command to the Invoker.");
	}
	mCmds.push_back(cmd);
}

void DPDrawing::Invoker::Invoke() {
	for(int i = 0; i < (int)mCmds.size(); i++) {
		if(mCmds.at(i) == nullptr) {
			SDL_Log("ERROR! Executing a NULLPTR in the Invoker!");
		}
		mCmds.at(i)->execute();
	}
	SDL_RenderPresent(renderer);
	mCmds.clear();
} 
