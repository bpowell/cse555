#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <SDL2/SDL.h>

#include <string>
#include <map>

#include "global.h"
#include "Sprite.h"

namespace dngine{
    class Screen{
        private:
            SDL_Renderer_ptr renderer;
            std::map<std::string, Sprite_ptr> sprites;
        public:
            Screen(SDL_Renderer_ptr r);
            ~Screen();
            SDL_Renderer_ptr get_renderer();
            void render();
            void add_sprite(std::string name, Sprite_ptr sprite);
    };

    typedef std::shared_ptr<Screen> Screen_ptr;
}

#endif
