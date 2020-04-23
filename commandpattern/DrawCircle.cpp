#include "DrawShape.h"
#include "Shape.h"

class DrawCircle : public DrawShape {
	
	private: DPDrawing::Shape desiredShape;

	public: 
	DrawCircle(DPDrawing::Shape desiredShape)
	{
		this->desiredShape = desiredShape;
	}

	void execute() 
	{
		desiredShape.DrawCircle();
	}
};
