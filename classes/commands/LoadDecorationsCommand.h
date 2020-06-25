#pragma once
#include "Command.h"
#include "../Rectangle.h"
#include "../Circle.h"
#include "../Shape.h"
#include "../decorators/ShapeTextDecorator.h"
#include "../decorators/ShapeTextTopDecorator.h"
#include "../decorators/ShapeTextLeftDecorator.h"
#include "../decorators/ShapeTextRightDecorator.h"
#include "../decorators/ShapeTextBottomDecorator.h"
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using std::vector;
using std::unique_ptr;
using std::string;
namespace DPDrawing {
	class LoadDecorationsCommand : public Command {
		private:
		vector<std::unique_ptr<ShapeTextDecorator>>* textDecorators = nullptr;
		vector<unique_ptr<Shape>>* shapes = nullptr;
		std::string load_path;
		SDL_Renderer* renderer = nullptr;
		Invoker* inv = nullptr;
		TextureManager* tm = nullptr;

		public:
		LoadDecorationsCommand(vector<unique_ptr<ShapeTextDecorator>>* textDecorators, vector<unique_ptr<Shape>>* shapes, std::string load_path, SDL_Renderer* renderer, Invoker* inv, TextureManager* tm) {
			this->textDecorators = textDecorators;
			this->shapes = shapes;
			this->load_path = load_path;
			this->renderer = renderer;
			this->inv = inv;
			this->tm = tm;
		}
		void execute() {
			std::ifstream i(load_path);
			json j;
			i >> j;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			string newShape = "";
			for(int i = 0; i < (int)j.size(); ++i) {
				for(int i = 0; i < (int)shapes->size(); i++) {
					SDL_Log("I'm in shapes for");
					if(shapes->at(i)->getUUID() == j[i]["shapeUUID"].get<string>()) {
						SDL_Log("I set newShape");
						newShape = shapes->at(i)->getUUID();
						break;
					}
				}
				if(newShape == "") {
					SDL_Log("ERROR: Cannot load this decoration because there is no currently loaded ShapeUUID that matches what it's looking for!");
				}
				else {
					// Center
					if (j[i]["type"].get<string>() == "ShapeTextDecorator") {
						SDL_Log("I got to here");
						ShapeTextDecorator r = ShapeTextDecorator(newShape, tm, shapes, renderer, inv);
						SDL_Log("I got to here 1");
						r.setUUID(j[i]["UUID"].get<string>());
						SDL_Log("I got to here 1.5");
						r.drawText(j[i]["text"].get<string>());
						SDL_Log("I got to here 2");
						textDecorators->push_back(std::make_unique<ShapeTextDecorator>(r));
						SDL_Log("I got to here 3");
					}
					// Top
					else if (j[i]["type"].get<string>() == "ShapeTextTopDecorator") {
					SDL_Log("I got to here");
						ShapeTextTopDecorator r = ShapeTextTopDecorator(newShape, tm, shapes, renderer, inv);
						r.setUUID(j[i]["UUID"].get<string>());
						r.drawText(j[i]["text"].get<string>());
						textDecorators->push_back(std::make_unique<ShapeTextDecorator>(r));
					}
					// Bottom
					else if (j[i]["type"].get<string>() == "ShapeTextBottomDecorator") {
					SDL_Log("I got to here");
						ShapeTextBottomDecorator r = ShapeTextBottomDecorator(newShape, tm, shapes, renderer, inv);
						r.setUUID(j[i]["UUID"].get<string>());
						r.drawText(j[i]["text"].get<string>());
						textDecorators->push_back(std::make_unique<ShapeTextDecorator>(r));
					}
					// Left
					else if (j[i]["type"].get<string>() == "ShapeTextLeftDecorator") {
					SDL_Log("I got to here");
						ShapeTextLeftDecorator r = ShapeTextLeftDecorator(newShape, tm, shapes, renderer, inv);
						r.setUUID(j[i]["UUID"].get<string>());
						r.drawText(j[i]["text"].get<string>());
						textDecorators->push_back(std::make_unique<ShapeTextDecorator>(r));
					}
					// Right
					else if (j[i]["type"].get<std::string>() == "ShapeTextRightDecorator") {
					SDL_Log("I got to here");
						ShapeTextRightDecorator r = ShapeTextRightDecorator(newShape, tm, shapes, renderer, inv);
						r.setUUID(j[i]["UUID"].get<string>());
						r.drawText(j[i]["text"].get<string>());
						textDecorators->push_back(std::make_unique<ShapeTextDecorator>(r));
					}
				}
			}
			i.close();
		}

		bool isUndoable() {
			return false;
		}
	};
}
