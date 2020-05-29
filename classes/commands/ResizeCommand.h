#pragma once
#include "Command.h"
#include "../Shape.h"
#include "../MouseHandler.h"

namespace DPDrawing {
	class ResizeCommand : public Command {
		private:
		Shape* s = nullptr;
		MouseHandler* mh = nullptr;

		public:
		ResizeCommand(Shape* s, MouseHandler* mh) {
			this->s = s;
			this->mh = mh;
		}
		void execute() {
			if(s == nullptr) {
				SDL_Log("ERROR: Shape to resize is NULLPTR!");
			}
			if(s == nullptr) {
				SDL_Log("ERROR: MouseHandler to resize with is NULLPTR!");
			}
			int holdingPosX = mh->getHoldingPosX();
			int holdingPosY = mh->getHoldingPosY();
			int centerX = s->getWidth() / 2;
			int centerY = s->getHeight() / 2;
			//if(s->getType() == "Rectangle" ) {
				// top left area
				if(holdingPosX < centerX && holdingPosY < centerY) {
					int previousPosY = s->getPosY();
					int previousPosX = s->getPosX();
					s->setPosX(mh->getMouseEndX());
					s->setPosY(mh->getMouseEndY());
					s->setWidth(s->getWidth() + (previousPosX - mh->getMouseEndX()));
					s->setHeight(s->getHeight() + (previousPosY - mh->getMouseEndY()));
				}
				// bottom left area
				else if(holdingPosX < centerX && holdingPosY > centerY) {
					int previousPosX = s->getPosX();
					s->setPosX(mh->getMouseEndX());
					s->setWidth(s->getWidth() + (previousPosX - s->getPosX()));
					s->setHeight(s->getHeight() + (mh->getMouseEndY() - mh->getMouseY()));
				}
				// top right area
				else if(holdingPosX > centerX && holdingPosY < centerY) {
					int previousPosY = s->getPosY();
					s->setPosY(mh->getMouseEndY());
					s->setHeight(s->getHeight() + (previousPosY - s->getPosY()));
					s->setWidth(s->getWidth() + (mh->getMouseEndX() - mh->getMouseX()));
				}
				// bottom right
				else if(holdingPosX > centerX && holdingPosY > centerY) {
					s->setWidth(s->getWidth() + (mh->getMouseEndX() - mh->getMouseX()));
					s->setHeight(s->getHeight() + (mh->getMouseEndY() - mh->getMouseY()));
				}
		}

	};
}
