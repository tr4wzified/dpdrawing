#include "DrawRectangle.h"

//Concrete klasse waar de DrawShape interface geimplementeerd is.

	void DPDrawing::DrawRectangle::Draw(Shape s)
	{
		desiredShape = s;
	}

	void DPDrawing::DrawRectangle::Execute()
	{
		Draw(desiredShape);
	}
