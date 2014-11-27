#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <SDL2/SDL.h>

#include <string>
#include <map>

#include "global.h"

namespace dngine{
    class Screen{
        private:
            SDL_Renderer_ptr renderer;
        public:
            Screen(SDL_Renderer_ptr r);
            ~Screen();
            SDL_Renderer_ptr get_renderer();
            void render();
    };

    typedef std::shared_ptr<Screen> Screen_ptr;
}

#endif
