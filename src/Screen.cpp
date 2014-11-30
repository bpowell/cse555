#include "Screen.h"

namespace dngine{
    Screen::Screen(SDL_Renderer_ptr r){
        renderer = r;
    }

    Screen::~Screen(){
    }

    SDL_Renderer_ptr Screen::get_renderer(){
        return renderer;
    }

    void Screen::render(){
        SDL_RenderClear(renderer.get());
		std::list<Sprite_ptr>::iterator it;

		for(it=sprites.begin(); it!=sprites.end(); ++it){
			Sprite_ptr sprite = *it;
			sprite->render();
		}

        SDL_RenderPresent(renderer.get());
    }

    void Screen::add_sprite(Sprite_ptr sprite) {
        sprites.push_back(sprite);
    }
}
