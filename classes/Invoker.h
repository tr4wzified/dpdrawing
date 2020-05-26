#pragma once
#include "SDL2/SDL.h"
#include "DrawCommand.h"
#include "TextureManager.h"
// Invoker
namespace DPDrawing {
	class Invoker {
	public:

		Invoker(SDL_Renderer* renderer, TextureManager* tm);
		void setDrawingColor(SDL_Color& c);
		void prepareToDraw(DrawCommand* cmd);
		void updateMouse(bool mouseBeingHeld);
		void updateMouseEnd(bool mouseBeingHeld);
		int getMouseX();
		int getMouseY();
		int getMouseEndX();
		int getMouseEndY();
		void Draw();

	private:
		bool mouseBeingHeld;
		vector<DrawCommand*> mCmds;
		SDL_Renderer* renderer;
		TextureManager* tm;
		int mouseX = 0;
		int mouseY = 0;

		int mouseEndX = 0;
		int mouseEndY = 0;

		SDL_Color drawingColor;
	};
}
