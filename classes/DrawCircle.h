#include "Circle.h"
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "DrawCommand.h"
namespace DPDrawing {
	class DrawCircle : public DrawCommand {
		public:
		DrawCircle(Circle* circ) {
			SDL_Log("Initializing DrawCircle");
			mCirc = circ;
		}
		void execute(SDL_Renderer* renderer, TextureManager* tm, int* mousePos1, int* mousePos2) {
			dynamicResize(mousePos1[0], mousePos1[1], mousePos2[0], mousePos2[1]);
			Draw(renderer);
		}
			
		private:
			#define DEFAULT_ELLIPSE_OVERSCAN 4
			int pixel(SDL_Renderer *renderer, Sint16 x, Sint16 y);
			int vline(SDL_Renderer * renderer, Sint16 x, Sint16 y1, Sint16 y2);
			int hline(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y);
			int _drawQuadrants(SDL_Renderer * renderer,  Sint16 x, Sint16 y, Sint16 dx, Sint16 dy, Sint32 f);
			int filledEllipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
			int pixelRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
			int pixelRGBAWeight(SDL_Renderer * renderer, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint32 weight);
			int vlineRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y1, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
			int hlineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
			int aaellipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
			int _ellipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Sint32 f);
			
			Circle* mCirc;
		void Draw(SDL_Renderer* renderer) {
			filledEllipseRGBA(renderer, mCirc->posX, mCirc->posY, mCirc->width, mCirc->height, (Uint8)255, (Uint8)255, (Uint8)255, (Uint8)255);
		}

		void dynamicResize(int mouseX, int mouseY, int mouseEndX, int mouseEndY) {
		    if (mouseEndX > mouseX && mouseEndY > mouseY) {
				mCirc->setPosX(mouseX);
				mCirc->setPosY(mouseY);
			}
		    else if (mouseEndX > mouseX && mouseEndY < mouseY) {
				mCirc->setPosX(mouseX);
				mCirc->setPosY(mouseEndY);
			}
		    else if (mouseEndX < mouseX && mouseEndY < mouseY) {
				mCirc->setPosX(mouseEndX);
				mCirc->setPosY(mouseEndY);
			}
			else {
				mCirc->setPosX(mouseEndX);
				mCirc->setPosY(mouseY);
		    }
			mCirc->setWidth(abs(mouseEndX - mouseX));
		    mCirc->setHeight(abs(mouseEndY - mouseY));
		}

	};
}
