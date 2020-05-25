#pragma once
namespace DPDrawing {
	class Selectable {
		public:
		virtual bool isSelected();
		virtual void Select();
		virtual void Deselect();
		private:
		bool selected = false;
	};
}
