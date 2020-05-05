#pragma once
#include <string.h>
#include <vector>
#include "DrawShape.h"
#include "Shape.h"
#include <memory>

namespace DPDrawing {
	class Drawer {
		public:
			Drawer(std::vector<std::unique_ptr<DrawShape>> drawList);
			Drawer();
			std::vector<std::unique_ptr<DrawShape>> drawList;
			void takeDrawRequest(std::unique_ptr<DrawShape>& DrawRequest);
			void executeDrawRequests();
	};
}
