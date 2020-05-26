#pragma once
#include <SDL2/SDL.h>
namespace DPDrawing {
	class MouseHandler {
		public:
		MouseHandler();
		void Update();
		void updateMouseBeingHeld();
		void updateHoldingPos(int x, int y);
		
		int getMouseY();
		int getMouseX();
		int getMouseEndX();
		int getMouseEndY();

		int getHoldingPosX();
		int getHoldingPosY();

		bool getMouseBeingHeld();
		int getHowLongBeingHeld();

		private:
		void updateBeginPos();
		void updateEndPos();
		struct Position {
			int x = 0;
			int y = 0;
		};
		Position beginPos;
		Position endPos;
		Position holdingPos;
		bool mouseBeingHeld = false;
		int howLongBeingHeld = 0;
		
	};
}

