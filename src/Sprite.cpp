#include "Sprite.h"

namespace dngine{
    Sprite::Sprite(SDL_Renderer_ptr r, std::string fname){
        renderer = r;
        filename = fname;
        image = SDL_Texture_ptr(IMG_LoadTexture(renderer.get(), filename.c_str()), SDL_DestroyTexture);
    }

    Sprite::~Sprite(){
    }

    SDL_Texture_ptr Sprite::get_texture(){
        return image;
    }

    void Sprite::set_location(SDL_Rect *loc){
        location = loc;
    }

    void Sprite::set_location(int x, int y, int h, int w){
        location->x = x;
        location->y = y;
        location->h = h;
        location->w = w;
    }

    SDL_Rect* Sprite::get_location() const{
        return location;
    }

    void Sprite::render(){
        SDL_RenderCopy(renderer.get(), image.get(), NULL, location);
    }
}
