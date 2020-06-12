#pragma once
#include "../Circle.h"
#include <SDL2/SDL.h>
#include "../SDL2_gfx_ellipse.h"
#include "../TextureManager.h"
#include "Command.h"

using DPDrawing::filledEllipseRGBA;

namespace DPDrawing {
	class DrawCircleCommand : public Command {
		public:
		DrawCircleCommand(Circle* circ, SDL_Renderer* r, TextureManager* tm) {
			mCirc = circ;
			this->r = r;
			this->tm = tm;
		}
		void execute() {
				SDL_Log("posX: %d posY: %d width: %d height: %d", mCirc->getPosX(), mCirc->getPosY(), mCirc->getWidth(), mCirc->getHeight());
				if (mCirc->isSelected()) {
					// Draw in red
					filledEllipseRGBA(r, mCirc->getPosX() + (mCirc->getWidth() / 2), mCirc->getPosY() + (mCirc->getHeight() / 2), mCirc->getWidth() / 2, mCirc->getHeight() / 2, (Uint8)255, (Uint8)0, (Uint8)0, (Uint8)255);
				}
				else {
					// Draw in white
					filledEllipseRGBA(r, mCirc->getPosX() + (mCirc->getWidth() / 2), mCirc->getPosY() + (mCirc->getHeight() / 2), mCirc->getWidth() / 2, mCirc->getHeight() / 2, (Uint8)255, (Uint8)255, (Uint8)255, (Uint8)255);
				}
				SDL_RenderPresent(r);
		}
		bool isUndoable() {
			return false;
		}
			
		private:
		SDL_Renderer* r;
		TextureManager* tm;
		Circle* mCirc;
	};
}
