#pragma once
namespace DPDrawing {
	class Command {
		public:
		//virtual ~Command() {}
		virtual void execute() = 0;
		virtual bool isUndoable() = 0;
	};
}
