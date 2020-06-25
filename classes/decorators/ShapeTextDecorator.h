#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../TextureManager.h"
#include "../Shape.h"
#include "../commands/DrawShapesCommand.h"
using std::string;
namespace DPDrawing {
	class ShapeTextDecorator : public Shape {
		protected:
			Shape* decoratedShape = nullptr;
			TextureManager* tm = nullptr;
			vector<unique_ptr<Shape>>* shapes = nullptr;
			SDL_Renderer* renderer = nullptr;
			Invoker* inv = nullptr;
		public:
			ShapeTextDecorator(Shape* decoratedShape, TextureManager* tm, vector<unique_ptr<Shape>>* shapes, SDL_Renderer* renderer, Invoker* inv) {
				this->decoratedShape = decoratedShape;
				this->tm = tm;
				this->shapes = shapes;
				this->renderer = renderer;
				this->inv = inv;
			}

			string getType() {
				return "ShapeTextDecorator";
			}

			void drawText(string text) {
				int texW = 0;
				int texH = 0;
				SDL_Surface* surface = TTF_RenderText_Solid(tm->getSmallFont(), text.c_str(), {0, 255, 0});
				SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
				SDL_Rect dstrect = { decoratedShape->getPosX() + (decoratedShape->getWidth() / 2) - (texW / 2), decoratedShape->getPosY() + (decoratedShape->getHeight() / 2) - (texH / 2), texW, texH };
				SDL_RenderCopy(renderer, texture, NULL, &dstrect);
				SDL_RenderPresent(renderer);
			}
	};
}
