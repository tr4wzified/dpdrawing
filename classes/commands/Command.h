#pragma once
#include <string>
namespace DPDrawing {
	class Command {
		public:
		virtual void execute() = 0;
	};
}
