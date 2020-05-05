#pragma once
#include "DrawShape.h"
#include "Shape.h"

namespace DPDrawing {
    class DrawRectangle : DrawShape
    {
        private:
        Shape desiredShape;
        void Draw(Shape desiredShape);
        public: 
        DrawRectangle(Shape shape);
        void Execute();
    };
}