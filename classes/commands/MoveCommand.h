#pragma once
#include "../Rectangle.h"
#include "../Invoker.h"
#include "../TextureManager.h"
#include "../MouseHandler.h"
#include "DrawCircleCommand.h"
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
using std::vector;
using std::unique_ptr;
namespace DPDrawing {
	class MoveCommand : public Command {
		private:
			Shape* s = nullptr;
			int posX = 0;
			int posY = 0;
			public:
			MoveCommand(Shape* s, int posX, int posY) {
				this->s = s;
				this->posX = posX;
				this->posY = posY;
			}
		void execute() {
			if(s == nullptr) {
				SDL_Log("ERROR: Trying to move a Shape that is NULLPTR in MoveCommand!");
			}
			s->setPosY(posY);
			s->setPosX(posX);
		}
		bool isUndoable() {
			return true;
		}
	};
}
