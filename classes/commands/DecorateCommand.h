#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include "../Shape.h"
#include "../decorators/ShapeTextDecorator.h"
#include "../decorators/ShapeTextTopDecorator.h"
#include "../decorators/ShapeTextBottomDecorator.h"
#include "../decorators/ShapeTextLeftDecorator.h"
#include "../decorators/ShapeTextRightDecorator.h"
using std::vector;
using std::unique_ptr;
namespace DPDrawing {
	class DecorateCommand : public Command {
		private:
			Shape* shapeToDecorate = nullptr;
			Invoker* inv = nullptr;
			TextureManager* tm = nullptr;
			vector<unique_ptr<Shape>>* shapes = nullptr;
			SDL_Renderer* renderer = nullptr;
			std::string userInput = "";
		public:
		DecorateCommand(Shape* shapeToDecorate, Invoker* inv, TextureManager* tm, vector<unique_ptr<Shape>>* shapes, SDL_Renderer* renderer) {
			this->shapeToDecorate = shapeToDecorate;
			this->inv = inv;
			this->tm = tm;
			this->shapes = shapes;
			this->renderer = renderer;
		}
		void execute() {
			if(shapeToDecorate != nullptr) {
				// Convert string to lowercase to make case insensitive input
				SDL_Log("Please enter where you want the text to appear! Choose: center, left, right, top, bottom");
				std::cin >> userInput;
				std::transform(userInput.begin(), userInput.end(), userInput.begin(), [](unsigned char c) {
						return std::tolower(c);
				});
				if(userInput == "center") {
					SDL_Log("Chose option center! Please enter the text you wish to appear in the center.");
					std::cin >> userInput;
					ShapeTextDecorator* sd = new ShapeTextDecorator(shapeToDecorate, tm, shapes, renderer, inv);
					sd->drawText(userInput);
					delete sd;
				}
				else if(userInput == "left") {
					SDL_Log("Chose option left! Please enter the text you wish to appear in the left.");
					std::cin >> userInput;
					ShapeTextLeftDecorator* ttl = new ShapeTextLeftDecorator(shapeToDecorate, tm, shapes, renderer, inv);
					ttl->drawText(userInput);
					delete ttl;
				}
				else if(userInput == "right") {
					SDL_Log("Chose option right! Please enter the text you wish to appear in the right.");
					std::cin >> userInput;
					ShapeTextRightDecorator* ttr = new ShapeTextRightDecorator(shapeToDecorate, tm, shapes, renderer, inv);
					ttr->drawText(userInput);
					delete ttr;
				}
				else if(userInput == "top") {
					SDL_Log("Chose option top! Please enter the text you wish to appear in the top.");
					std::cin >> userInput;
					ShapeTextTopDecorator* ttd = new ShapeTextTopDecorator(shapeToDecorate, tm, shapes, renderer, inv);
					ttd->drawText(userInput);
					delete ttd;
				}
				else if(userInput == "bottom") {
					SDL_Log("Chose option bottom! Please enter the text you wish to appear on the bottom.");
					std::cin >> userInput;
					ShapeTextBottomDecorator* ttb = new ShapeTextBottomDecorator(shapeToDecorate, tm, shapes, renderer, inv);
					ttb->drawText(userInput);
					delete ttb;
				}
				else {
					SDL_Log("Unrecognized input. Please try again.");
				}
			}
			else {
				SDL_Log("No selected shapes found to decorate!");
			}
		}
		bool isUndoable() {
			return false;
		}
	};
}
