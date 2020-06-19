#pragma once
#include "../../Circle.h"
#include <SDL2/SDL.h>
#include "../../SDL2_gfx_ellipse.h"
#include "../../TextureManager.h"
#include "Strategy.h"

using DPDrawing::filledEllipseRGBA;

namespace DPDrawing {
	class DrawCircleStrategy : public Strategy {
		public:
		DrawCircleStrategy(Circle* circ, SDL_Renderer* r, TextureManager* tm) {
			mCirc = circ;
			this->r = r;
			this->tm = tm;
		}
		void execute() {
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

		private:
		SDL_Renderer* r;
		TextureManager* tm;
		Circle* mCirc;
	};
}
