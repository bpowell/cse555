#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <string>
#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

#include "global.h"

namespace dngine{
    class Sprite{
        protected:
            SDL_Renderer_ptr renderer;
            std::string filename;
            SDL_Texture_ptr image;
            SDL_Rect *location;
            SDL_Rect *size;
            SDL_Rect *clip;
            int pos_x;
            int pos_y;
        public:
            Sprite(SDL_Renderer_ptr r, std::string fname, SDL_Rect *location);
            Sprite(SDL_Renderer_ptr r, std::string fname, SDL_Rect *location, SDL_Rect *size, int x, int y);
            ~Sprite();
            SDL_Texture_ptr get_texture();
            void set_location(SDL_Rect *loc);
            void set_location(int x, int y, int h, int w);
            SDL_Rect *get_location() const;
            void set_clip(SDL_Rect *c);
            void render();
    };

    typedef std::shared_ptr<Sprite> Sprite_ptr;
}

#endif
