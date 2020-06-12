#pragma once
namespace DPDrawing {
	class Command {
		public:
		virtual void execute() = 0;
		virtual bool isUndoable() = 0;
	};
}
