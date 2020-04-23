#include "DrawRectangle.h"
#include "DrawShape.h"
#include "Shape.h"

class DrawRectangle : public DrawShape {
	
	private: DPDrawing::Shape desiredShape;

	public:
	DrawRectangle(DPDrawing::Shape desiredShape)
	{
		this->desiredShape = desiredShape;
	}

	void execute() 
	{
		desiredShape.DrawRectangle();
	}
};
