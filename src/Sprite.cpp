#include "Sprite.h"

namespace dngine{
    Sprite::Sprite(SDL_Renderer_ptr r, std::string fname, SDL_Rect *location) :
        renderer(r), filename(fname), location(location), size(NULL), clip(NULL){
        image = SDL_Texture_ptr(IMG_LoadTexture(renderer.get(), filename.c_str()), SDL_DestroyTexture);
    }

    Sprite::Sprite(SDL_Renderer_ptr r, std::string fname, SDL_Rect *location, SDL_Rect *size, int x, int y)
        : renderer(r), filename(fname), location(location), size(size), pos_x(x), pos_y(y) {
        image = SDL_Texture_ptr(IMG_LoadTexture(renderer.get(), filename.c_str()), SDL_DestroyTexture);
        clip = new SDL_Rect();
        clip->x = pos_x * size->w;
        clip->y = pos_y * size->h;
        clip->w = size->w;
        clip->h = size->h;
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
        SDL_RenderCopy(renderer.get(), image.get(), clip, location);
    }
}
