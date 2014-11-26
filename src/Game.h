#ifndef _GAME_H_
#define _GAME_H_

#include <SDL2/SDL.h>

#include <string>
#include <memory>

#include "global.h"

namespace dngine{
	class Game{
		private:
			SDL_Window_ptr window;
		public:
			Game(std::string name, int width, int height);
			~Game();
			SDL_Window_ptr get_window();
			void render();
	};
}

#endif
