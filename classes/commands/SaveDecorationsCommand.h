#pragma once
#include "Command.h"
#include "../decorators/ShapeTextDecorator.h"
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
using std::vector;
using std::unique_ptr;
using json = nlohmann::json;

namespace DPDrawing {
	class SaveDecorationsCommand : public Command {
		private:
			vector<unique_ptr<ShapeTextDecorator>>* textDecorators = nullptr;
			std::string save_path;
		public:
		SaveDecorationsCommand(vector<unique_ptr<ShapeTextDecorator>>* textDecorators, std::string save_path) {
			this->textDecorators = textDecorators;
			this->save_path = save_path;
		}
		void execute() {
			json jsonObjects = json::array();
			for(int i = 0; i < (int)textDecorators->size(); ++i) {
			    jsonObjects.push_back(json::object());
				jsonObjects[i]["type"] = textDecorators->at(i)->getType();
				jsonObjects[i]["UUID"] = textDecorators->at(i)->getUUID();
				SDL_Log("Getting Shape UUID");
				jsonObjects[i]["shapeUUID"] = textDecorators->at(i)->getShapeUUID();
				SDL_Log("Got Shape UUID");
				jsonObjects[i]["text"] = textDecorators->at(i)->getText();
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
