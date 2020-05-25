#include "Circle.h"
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "DrawCommand.h"
namespace DPDrawing {
	class DrawCircle : public DrawCommand {
		public:
		DrawCircle(Circle* circ) {
			mCirc = circ;
		}
		void execute(SDL_Renderer* renderer, TextureManager* tm) {
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
				if (mCirc->isSelected()) {
/* 	return Shape::getPosX() + (Shape::getWidth() / 2); */
					filledEllipseRGBA(renderer, mCirc->getPosX() + (mCirc->getWidth() / 2), mCirc->getPosY() + (mCirc->getHeight() / 2), mCirc->getWidth() / 2, mCirc->getHeight() / 2, (Uint8)255, (Uint8)0, (Uint8)0, (Uint8)255);
				}
				else {
					filledEllipseRGBA(renderer, mCirc->getPosX() + (mCirc->getWidth() / 2), mCirc->getPosY() + (mCirc->getHeight() / 2), mCirc->getWidth() / 2, mCirc->getHeight() / 2, (Uint8)255, (Uint8)255, (Uint8)255, (Uint8)255);
				}
			}


	};
}
