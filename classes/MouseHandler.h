#include <SDL2/SDL.h>
namespace DPDrawing {
	class MouseHandler {
		public:
		MouseHandler();
		void Update();
		int getBeginPosX();
		int getBeginPosY();
		int getEndPosX();
		int getEndPosY();
		void updateMouseBeingHeld();

		private:
		void updateBeginPos();
		void updateEndPos();
		struct Position {
			int x = 0;
			int y = 0;
		};
		Position beginPos;
		Position endPos;
		bool mouseBeingHeld = false;
		int howLongBeingHeld = 0;
		
	};
}

