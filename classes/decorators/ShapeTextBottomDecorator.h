#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "../Invoker.h"
#include "../Shape.h"
#include "ShapeTextDecorator.h"
using std::string;
namespace DPDrawing {
	class ShapeTextBottomDecorator : public ShapeTextDecorator {
		public:
		ShapeTextBottomDecorator(string shapeUUID, TextureManager* tm, vector<unique_ptr<Shape>>* shapes, SDL_Renderer* renderer, Invoker* inv) : ShapeTextDecorator(shapeUUID, tm, shapes, renderer, inv) {
		}
		string getType() {
			return "ShapeTextBottomDecorator";
		}
		void drawText(string text) {
			Shape* decoratedShape = nullptr;
			for(int i = 0; i < (int)shapes->size(); i++) {
				if(shapes->at(i)->getUUID() == shapeUUID) {
					decoratedShape = shapes->at(i).get();
					break;
				}
			}
			this->text = text;
			int texW = 0;
			int texH = 0;
			SDL_Surface* surface = TTF_RenderText_Solid(tm->getSmallFont(), text.c_str(), {255, 255, 255});
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
			SDL_Rect dstrect = { decoratedShape->getPosX() + (decoratedShape->getWidth() / 2) - (texW / 2), (decoratedShape->getPosY() + decoratedShape->getHeight()) - (texH / 2) + 20, texW, texH };
			SDL_RenderCopy(renderer, texture, NULL, &dstrect);
			SDL_RenderPresent(renderer);
		}
	};
}
