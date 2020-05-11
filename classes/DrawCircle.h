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
		void execute(SDL_Renderer* renderer, TextureManager* tm, int mouseX, int mouseY, int mouseEndX, int mouseEndY) {
			dynamicResize(mouseX, mouseY, mouseEndX, mouseEndY);
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
				if (!mCirc->isSelected) {
					filledEllipseRGBA(renderer, mCirc->getPosX(), mCirc->getPosY(), mCirc->getRadiusX(), mCirc->getRadiusY(), (Uint8)255, (Uint8)255, (Uint8)255, (Uint8)255);
				}
				else {
					filledEllipseRGBA(renderer, mCirc->getPosX(), mCirc->getPosY(), mCirc->getRadiusX(), mCirc->getRadiusY(), (Uint8)255, (Uint8)0, (Uint8)0, (Uint8)255);
				}
			}

		void dynamicResize(int mouseX, int mouseY, int mouseEndX, int mouseEndY) {
			
			// topleft to bottomright
		    if (mouseEndX > mouseX && mouseEndY > mouseY) {
			}
			// bottomleft to topright
		    else if (mouseEndX > mouseX && mouseEndY < mouseY) {
				int temp = mouseY;
				mouseY = mouseEndY;
				mouseEndY = temp;
			}
			// bottomright to topleft
		    else if (mouseEndX < mouseX && mouseEndY < mouseY) {
				int temp = mouseX;
				mouseX = mouseEndX;
				mouseEndX = temp;

				temp = mouseY;
				mouseY = mouseEndY;
				mouseEndY = temp;
			}
			// topright to bottomleft
			else {
				int temp = mouseX;
				mouseX = mouseEndX;
				mouseEndX = temp;
		    }

			int middelX = (mouseX + mouseEndX) / 2;
			int middelY = (mouseY + mouseEndY) / 2;
			mCirc->setPosX(middelX); 
			mCirc->setPosY(middelY); 
			int radiusX = (mouseEndX - mouseX) / 2;
			int radiusY = (mouseEndY - mouseY) / 2;
			mCirc->setRadiusX(radiusX);
			mCirc->setRadiusY(radiusY);
		}

	};
}
