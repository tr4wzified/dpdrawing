#pragma once
#include "Command.h"
#include "../Rectangle.h"
#include "../Circle.h"
#include "../Shape.h"
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using std::vector;
namespace DPDrawing {
	class LoadCommand : public Command {
		private:
		vector<std::unique_ptr<Shape>>* shapes;
		std::string load_path;
		SDL_Renderer* renderer = nullptr;

		public:
		LoadCommand(vector<std::unique_ptr<Shape>>* shapes, std::string load_path, SDL_Renderer* renderer) {
			this->shapes = shapes;
			this->load_path = load_path;
			this->renderer = renderer;
		}
		void execute() {
			std::ifstream i(load_path);
			json j;
			i >> j;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			for(int i = 0; i < (int)j.size(); ++i) {
				if (j[i]["type"].get<std::string>() == "Rectangle") {
					Rectangle r = Rectangle(j[i]["width"].get<int>(), j[i]["height"].get<int>(), j[i]["posX"].get<int>(), j[i]["posY"].get<int>());
					r.setUUID(j[i]["UUID"].get<string>());
					shapes->push_back(std::make_unique<Rectangle>(r));
				}
				else if (j[i]["type"].get<std::string>() == "Circle") {
					Circle r = Circle(j[i]["width"].get<int>(), j[i]["height"].get<int>(), j[i]["posX"].get<int>(), j[i]["posY"].get<int>());
					r.setUUID(j[i]["UUID"].get<string>());
					shapes->push_back(std::make_unique<Circle>(r));
				}
			}
			i.close();
		}

		bool isUndoable() {
			return false;
		}
	};
}
