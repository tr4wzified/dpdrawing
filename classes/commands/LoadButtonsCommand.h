#pragma once
#include <SDL2/SDL.h>
#include "Command.h"
#include "../TextureManager.h"
#include "../Button.h"
#include "../Rectangle.h"
#include "../Circle.h"
#include "../Shape.h"
#include <vector>
#include <memory>
#include <string>
using std::vector;
namespace DPDrawing {
	class LoadButtonsCommand : public Command {
		private:
		SDL_Renderer* renderer = nullptr;
		int* currentMode = nullptr;
		const int BUTTON_WIDTH = 75;
		const int BUTTON_HEIGHT = 75;
		TTF_Font* font = nullptr;
		TextureManager* tm = nullptr;
		const int* button_height = nullptr;
		const int* button_width = nullptr;

		public:
		LoadButtonsCommand(SDL_Renderer* renderer, TTF_Font* font, TextureManager* tm, int* currentMode, const int* button_width, const int* button_height) {
			this->renderer = renderer;
			this->font = font;
			this->tm = tm;
			this->currentMode = currentMode;
			this->button_width = button_width;
			this->button_height = button_height;
		}

		void execute() {
			if(renderer == nullptr) {
				SDL_Log("ERROR: renderer is nullptr in LoadButtonsCommand");
			}
			if(font == nullptr) {
				SDL_Log("ERROR: font is nullptr in LoadButtonsCommand");
			}
			if(tm == nullptr) {
				SDL_Log("ERROR: tm is nullptr in LoadButtonsCommand");
			}
			if(currentMode == nullptr) {
				SDL_Log("ERROR: currentMode is nullptr in LoadButtonsCommand");
			}
			if(button_width == nullptr) {
				SDL_Log("ERROR: button_width is nullptr in LoadButtonsCommand");
			}
			if(button_height == nullptr) {
				SDL_Log("ERROR: button_height is nullptr in LoadButtonsCommand");
			}

			SDL_Texture* button_tex = tm->getTextureByName("button");
			SDL_Texture* button_active = tm->getTextureByName("button-active");

			if(button_tex == nullptr) {
				SDL_Log("ERROR: button is nullptr in LoadButtonsCommand");
			}
			if(button_active == nullptr) {
				SDL_Log("ERROR: button-active is nullptr in LoadButtonsCommand");
			}

			SDL_Color text = {255,255,255};

			// Button -7 - Redo - Vertical
			Button t(0, BUTTON_HEIGHT * 8, text, 71, font);
			SDL_Rect* t_rect = t.getRectangle();
			SDL_Texture* t_msg = SDL_CreateTextureFromSurface(renderer, t.getSurface());
			SDL_Rect* t_msg_rect = t.getRectangle();
			if(*currentMode == -7) {
				SDL_RenderCopy(renderer, button_active, NULL, t_rect);
			}
			else {
				SDL_RenderCopy(renderer, button_tex, NULL, t_rect);
			}
			SDL_RenderCopy(renderer, t_msg, NULL, t_msg_rect);

			// Button -7 - Redo - Vertical
			Button u(0, BUTTON_HEIGHT * 7, text, 62, font);
			SDL_Rect* u_rect = u.getRectangle();
			SDL_Texture* u_msg = SDL_CreateTextureFromSurface(renderer, u.getSurface());
			SDL_Rect* u_msg_rect = u.getRectangle();
			if(*currentMode == -7) {
				SDL_RenderCopy(renderer, button_active, NULL, u_rect);
			}
			else {
				SDL_RenderCopy(renderer, button_tex, NULL, u_rect);
			}
			SDL_RenderCopy(renderer, u_msg, NULL, u_msg_rect);

			// Button -6 - Undo - Vertical
			Button v(0, BUTTON_HEIGHT * 6, text, 60, font);
			SDL_Rect* v_rect = v.getRectangle();
			SDL_Texture* v_msg = SDL_CreateTextureFromSurface(renderer, v.getSurface());
			SDL_Rect* v_msg_rect = v.getRectangle();
			if(*currentMode == -6) {
				SDL_RenderCopy(renderer, button_active, NULL, v_rect);
			}
			else {
				SDL_RenderCopy(renderer, button_tex, NULL, v_rect);
			}
			SDL_RenderCopy(renderer, v_msg, NULL, v_msg_rect);

			// Button -5 - Resize - Vertical
			Button w(0, BUTTON_HEIGHT * 5, text, 124, font);
			SDL_Rect* w_rect = w.getRectangle();
			SDL_Texture* w_msg = SDL_CreateTextureFromSurface(renderer, w.getSurface());
			SDL_Rect* w_msg_rect = w.getRectangle();
			if(*currentMode == -5) {
				SDL_RenderCopy(renderer, button_active, NULL, w_rect);
			}
			else {
				SDL_RenderCopy(renderer, button_tex, NULL, w_rect);
			}
			SDL_RenderCopy(renderer, w_msg, NULL, w_msg_rect);

			// Button -4 - Delete - Vertical
			Button x(0, BUTTON_HEIGHT * 4, text, 68, font);
			SDL_Rect* x_rect = x.getRectangle();
			SDL_Texture* x_msg = SDL_CreateTextureFromSurface(renderer, x.getSurface());
			SDL_Rect* x_msg_rect = x.getRectangle();
			if(*currentMode == -4) {
				SDL_RenderCopy(renderer, button_active, NULL, x_rect);
			}
			else {
				SDL_RenderCopy(renderer, button_tex, NULL, x_rect);
			}
			SDL_RenderCopy(renderer, x_msg, NULL, x_msg_rect);

			// Button -3 - JSON Load - Vertical
			Button y(0, BUTTON_HEIGHT * 3, text, 76, font);
			SDL_Rect* y_rect = y.getRectangle();
			SDL_Texture* y_msg = SDL_CreateTextureFromSurface(renderer, y.getSurface());
			SDL_Rect* y_msg_rect = y.getRectangle();
			if(*currentMode == -3) {
				SDL_RenderCopy(renderer, button_active, NULL, y_rect);
			}
			else {
				SDL_RenderCopy(renderer, button_tex, NULL, y_rect);
			}
			SDL_RenderCopy(renderer, y_msg, NULL, y_msg_rect);

			// Button -2 - JSON Save - Vertical
			Button z(0, BUTTON_HEIGHT * 2, text, 74, font);
			SDL_Rect* z_rect = z.getRectangle();
			SDL_Texture* z_msg = SDL_CreateTextureFromSurface(renderer, z.getSurface());
			SDL_Rect* z_msg_rect = z.getRectangle();
			if(*currentMode == -2) {
				SDL_RenderCopy(renderer, button_active, NULL, z_rect);
			}
			else {
				SDL_RenderCopy(renderer, button_tex, NULL, z_rect);
			}
			SDL_RenderCopy(renderer, z_msg, NULL, z_msg_rect);

			// Button -1 - Select - Vertical
			Button a(0, BUTTON_HEIGHT, text, 83, font);
			SDL_Rect* a_rect = a.getRectangle();
			SDL_Texture* a_msg = SDL_CreateTextureFromSurface(renderer, a.getSurface());
			SDL_Rect* a_msg_rect = a.getRectangle();
			if(*currentMode == -1) {
				SDL_RenderCopy(renderer, button_active, NULL, a_rect);
			}
			else {
				SDL_RenderCopy(renderer, button_tex, NULL, a_rect);
			}
			SDL_RenderCopy(renderer, a_msg, NULL, a_msg_rect);

			// Button 1 - Reset
			Button b(0, 0, text, 88, font);
			SDL_Rect* b_rect = b.getRectangle();
			SDL_Texture* b_msg = SDL_CreateTextureFromSurface(renderer, b.getSurface());
			SDL_Rect* b_msg_rect = b.getRectangle();
			if(currentMode == 0) {
				SDL_RenderCopy(renderer, button_active, NULL, b_rect);
			}
			else {
				SDL_RenderCopy(renderer, button_tex, NULL, b_rect);
			}
			SDL_RenderCopy(renderer, b_msg, NULL, b_msg_rect);

			// Button 2 - Rectangle - R
			Button c(BUTTON_WIDTH, 0, text, 82, font);
			SDL_Rect* c_rect = c.getRectangle();
			SDL_Texture* c_msg = SDL_CreateTextureFromSurface(renderer, c.getSurface());
			SDL_Rect* c_msg_rect = c.getRectangle();
			if(*currentMode == 1) {
				SDL_RenderCopy(renderer, button_active, NULL, c_rect);
			}
			else {
				SDL_RenderCopy(renderer, button_tex, NULL, c_rect);
			}
			SDL_RenderCopy(renderer, c_msg, NULL, c_msg_rect);

			// Button 3 - Ellipse - O
			Button d(BUTTON_WIDTH * 2, 0, text, 79, font);
			SDL_Rect* d_rect = d.getRectangle();
			SDL_Texture* d_msg = SDL_CreateTextureFromSurface(renderer, d.getSurface());
			SDL_Rect* d_msg_rect = d.getRectangle();
			if(*currentMode == 2) {
				SDL_RenderCopy(renderer, button_active, NULL, d_rect);
			}
			else {
				SDL_RenderCopy(renderer, button_tex, NULL, d_rect);
			}
			SDL_RenderCopy(renderer, d_msg, NULL, d_msg_rect);

			SDL_RenderPresent(renderer);

			// Destroy
			SDL_DestroyTexture(u_msg);
			SDL_DestroyTexture(v_msg);
			SDL_DestroyTexture(w_msg);
			SDL_DestroyTexture(x_msg);
			SDL_DestroyTexture(y_msg);
			SDL_DestroyTexture(z_msg);
			SDL_DestroyTexture(a_msg);
			SDL_DestroyTexture(b_msg);
			SDL_DestroyTexture(c_msg);
			SDL_DestroyTexture(d_msg);
			}
		bool isUndoable() {
			return false;
		}
	};
}


