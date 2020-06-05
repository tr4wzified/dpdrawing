#include "MouseHandler.h"
#include <SDL2/SDL.h>
namespace DPDrawing {
	class ButtonHandler {
		private:
			MouseHandler* mh;
		public:
			ButtonHandler(MouseHandler* mh, int button_width, int button_height);
			bool checkIfButtonPressed();
			bool initializeButtons();
	};
}
