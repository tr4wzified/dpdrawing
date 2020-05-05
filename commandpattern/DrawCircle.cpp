#include "DrawCircle.h"

//Concrete klasse waar de DrawShape interface geimplementeerd is.

	void DPDrawing::DrawCircle::Draw(Shape desiredShape)
	{
		this->desiredShape = desiredShape;
	}
	
	void DPDrawing::DrawCircle::Execute()
	{
		Draw(desiredShape);
	}
