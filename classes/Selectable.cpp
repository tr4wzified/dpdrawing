#include "Selectable.h"
bool DPDrawing::Selectable::isSelected() {
	return selected;
}

void DPDrawing::Selectable::Select() {
	selected = true;
}

void DPDrawing::Selectable::Deselect() {
	selected = false;
}

