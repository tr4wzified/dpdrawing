#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "../TextureManager.h"
#include "../Shape.h"
#include "../commands/DrawShapesCommand.h"
using std::string;
namespace DPDrawing {
	class ShapeDecorator : public Shape {
		protected:
			Shape* decoratedShape = nullptr;
			TextureManager* tm = nullptr;
			vector<unique_ptr<Shape>>* shapes = nullptr;
			SDL_Renderer* renderer = nullptr;
			Invoker* inv = nullptr;
		public:
			ShapeDecorator(Shape* decoratedShape, TextureManager* tm, vector<unique_ptr<Shape>>* shapes, SDL_Renderer* renderer, Invoker* inv) {
				this->decoratedShape = decoratedShape;
				this->tm = tm;
				this->shapes = shapes;
				this->renderer = renderer;
				this->inv = inv;
			}
			/* void draw() { */
			/* 	DrawShapesCommand* dsc = new DrawShapesCommand(tm, shapes, renderer); */
			/* 	inv->addCommand(dsc); */
			/* 	inv->Invoke(); */
			/* } */
			string getType() {
				return "ShapeDecorator";
			}
	};
}
