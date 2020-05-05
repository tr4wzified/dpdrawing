#include "Shape.h"

//De request class, dit is het object waar we commando's op willen uitoefenen 
    void DPDrawing::Shape::setName(std::string name){
        this->name = name;
    }

    void DPDrawing::Shape::setSize(int width, int height, int posX, int posY){
        this->width = width;
        this->height = height;
        this->posX = posX;
        this->posY = posY;
        
    }

    //Draw rectangle if selected
    void DPDrawing::Shape::Draw(int mouseX, int mouseY, int mouseEndX, int mouseEndY) {

        SDL_Rect rect;
        
        rect.w = width;
        rect.h = height;
        rect.x = posX;
        rect.y = posY;

        //make sure square is drawable from all corners
        if (mouseEndX > mouseX && mouseEndY > mouseY) {
    	    posX = mouseX;
    	    posY = mouseY;
        }
        else if (mouseEndX < mouseEndX && mouseEndY > mouseY) {
        	posX = mouseEndX;
        	posY = mouseY;
        }
        else if (mouseEndX > mouseX && mouseEndY < mouseY) {
    	    posX = mouseX;
    	    posY = mouseEndY;
        }
        else if(mouseEndX < mouseX && mouseEndY < mouseY) {
        	posX = mouseEndX;
        	posY = mouseEndY;
        }
        else {
        	posX = mouseEndX;
        	posY = mouseY;
        }

        std::cout << "Rectangle was drawn" << std::endl;
    }

    //draw circle if selected
    void DPDrawing::Shape::drawCircle()
    {
        std::cout << "Circle was drawn" << std::endl;
    }