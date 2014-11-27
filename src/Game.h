#ifndef _GAME_H_
#define _GAME_H_

#include <SDL2/SDL.h>

#include <string>
#include <memory>

#include "global.h"
#include "Screen.h"

namespace dngine{
	class Game{
		private:
			SDL_Window_ptr window;
            Screen_ptr screen;
		public:
			Game(std::string name, int width, int height);
			~Game();
			SDL_Window_ptr get_window();
            Screen_ptr create_screen();
			void render();
	};
}

#endif
