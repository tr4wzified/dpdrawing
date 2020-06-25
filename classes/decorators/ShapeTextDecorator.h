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
			string text = "";
			string shapeUUID = "";
		public:
			ShapeTextDecorator(string shapeUUID, TextureManager* tm, vector<unique_ptr<Shape>>* shapes, SDL_Renderer* renderer, Invoker* inv) {
				this->shapeUUID = shapeUUID;
				this->tm = tm;
				this->shapes = shapes;
				this->renderer = renderer;
				this->inv = inv;
				// Generate UUID
				static std::random_device rd;
				static std::mt19937 gen(rd());
				static std::uniform_int_distribution<> dis(0, 15);
				static std::uniform_int_distribution<> dis2(8, 11);
				std::stringstream ss;
				int i;
				ss << std::hex;
				for (i = 0; i < 8; i++) {
				    ss << dis(gen);
				}
				ss << "-";
				for (i = 0; i < 4; i++) {
				    ss << dis(gen);
				}
				ss << "-4";
				for (i = 0; i < 3; i++) {
				    ss << dis(gen);
				}
				ss << "-";
				ss << dis2(gen);
				for (i = 0; i < 3; i++) {
				    ss << dis(gen);
				}
				ss << "-";
				for (i = 0; i < 12; i++) {
				    ss << dis(gen);
				};
				this->setUUID(ss.str());
			}

			string getType() {
				return "ShapeTextDecorator";
			}

			string getShapeUUID() {
				return shapeUUID;
			}

			string getText() {
				return text;
			}

			void drawText(string text) {
				Shape* decoratedShape = nullptr;
				for(int i = 0; i < (int)shapes->size(); i++) {
					SDL_Log("Looking for shape with UUID %s", shapeUUID.c_str());
					if(shapes->at(i)->getUUID() == shapeUUID) {
						SDL_Log("UUID found, shape has been set");
						decoratedShape = shapes->at(i).get();
						break;
					}
				}
				if(decoratedShape == nullptr) {
					SDL_Log("ERROR: No shape found with UUID provided! UUID provided: %s", shapeUUID.c_str());
				}
				this->text = text;
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
