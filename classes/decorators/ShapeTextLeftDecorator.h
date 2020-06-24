#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "../Invoker.h"
#include "../Shape.h"
#include "ShapeTextDecorator.h"
using std::string;
namespace DPDrawing {
	class ShapeTextLeftDecorator : public ShapeTextDecorator {
		public:
		ShapeTextLeftDecorator(Shape* decoratedShape, TextureManager* tm, vector<unique_ptr<Shape>>* shapes, SDL_Renderer* renderer, Invoker* inv) : ShapeTextDecorator(decoratedShape, tm, shapes, renderer, inv) {
		}
		string getType() {
			return "ShapeTextLeftDecorator";
		}
		void drawText(string text) {
			int texW = 0;
			int texH = 0;
			SDL_Surface* surface = TTF_RenderText_Solid(tm->getSmallFont(), text.c_str(), {255, 255, 255});
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
			SDL_Rect dstrect = { decoratedShape->getPosX() - texW - 50, decoratedShape->getPosY() + (decoratedShape->getHeight() / 2) - (texH / 2), texW, texH };
			SDL_RenderCopy(renderer, texture, NULL, &dstrect);
			SDL_RenderPresent(renderer);
		}
	};
}