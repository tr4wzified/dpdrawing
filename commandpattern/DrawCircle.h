#pragma once
#include "DrawShape.h"
#include "Shape.h"

namespace DPDrawing {
    class DrawCircle
    {
        public: 
        void Draw(Shape desiredShape);
        void Execute();

        private: Shape desiredShape;
    };
}