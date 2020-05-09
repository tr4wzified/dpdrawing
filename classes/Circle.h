#pragma once
#include <SDL2/SDL.h>
#include "Shape.h"
namespace DPDrawing {
	class Circle: public Shape {
		public:
			#define DEFAULT_ELLIPSE_OVERSCAN 4
			Circle(int width, int height, int posX, int posY);
			Circle();
			float getArea();
			void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius, SDL_Color c);
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

	};
}
