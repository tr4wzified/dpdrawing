#pragma once
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include "../../Invoker.h"
#include "../../TextureManager.h"

using std::unique_ptr;
using std::vector;
namespace DPDrawing {
	class Strategy {
		public:
		virtual void execute() = 0;
		virtual ~Strategy();
	};
}
