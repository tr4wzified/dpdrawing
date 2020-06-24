#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "../Invoker.h"
#include "../Shape.h"
#include "ShapeDecorator.h"
using std::string;
namespace DPDrawing {
	class TextTopDecorator : public ShapeDecorator {
		public:
		TextTopDecorator(Shape* decoratedShape, TextureManager* tm, vector<unique_ptr<Shape>>* shapes, SDL_Renderer* renderer, Invoker* inv) : ShapeDecorator(decoratedShape, tm, shapes, renderer, inv) {
		}
		string getType() {
			return "TextTopDecorator";
		}
		void draw();

	};
}
