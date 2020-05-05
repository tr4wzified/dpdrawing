#pragma once
#include<stdlib.h>
#include<string>
#include<iostream>
#include<SDL2/SDL.h>
#include "../classes/Rectangle.h"

namespace DPDrawing{
	class Shape {
		public:
		    std::string name = "Empty Shape";
    		int width, height, posX, posY;
			void setName(std::string name);
			void setSize(int width, int height, int posX, int posY);
			void Draw(int mouseX, int mouseY, int mouseEndX, int mouseEndY);
			void drawCircle();
	};
}

