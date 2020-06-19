#pragma once
#include <SDL2/SDL.h>
#include "Strategy.h"
namespace DPDrawing {
	class Context {
		private:
			Strategy* strategy;
		public:
			Context(Strategy* strategy) {
				this->strategy = strategy;
				if(strategy == nullptr) {
					SDL_Log("WARNING: Adding NULLPTR as Strategy in Context!");
				}
			}
			~Context() {
				delete strategy;
			}
			void executeStrategy() {
				strategy->execute();
			}
	};
}
