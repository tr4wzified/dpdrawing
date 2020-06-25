#pragma once
#include "Command.h"
#include "../Shape.h"
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
using std::vector;
using std::unique_ptr;
using json = nlohmann::json;

namespace DPDrawing {
	class SaveCommand : public Command {
		private:
			vector<unique_ptr<Shape>>* shapes;
			std::string save_path;
		public:
		SaveCommand(vector<unique_ptr<Shape>>* shapes, std::string save_path) {
			this->shapes = shapes;
			this->save_path = save_path;
		}
		void execute() {
			json jsonObjects = json::array();
			for(int i = 0; i < (int)shapes->size(); ++i) {
			    jsonObjects.push_back(json::object());
				jsonObjects[i]["type"] = shapes->at(i)->getType();
				jsonObjects[i]["width"] = shapes->at(i)->getWidth();
				jsonObjects[i]["height"] = shapes->at(i)->getHeight();
				jsonObjects[i]["posX"] = shapes->at(i)->getPosX();
				jsonObjects[i]["posY"] = shapes->at(i)->getPosY();
				jsonObjects[i]["UUID"] = shapes->at(i)->getUUID();
			}
		
			std::ofstream myfile(save_path);
			myfile << jsonObjects;
			myfile.close();
		}
		bool isUndoable() {
			return false;
		}

	};
}
