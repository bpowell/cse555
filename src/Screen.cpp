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
		std::map<std::string, Sprite_ptr>::iterator it;

		for(it=sprites.begin(); it!=sprites.end(); ++it){
			Sprite_ptr sprite = it->second;
			sprite.get()->render();
		}

        SDL_RenderPresent(renderer.get());
    }

    void Screen::add_sprite(std::string name, Sprite_ptr sprite) {
        sprites.insert(std::pair<std::string,Sprite_ptr>(name,sprite));
    }
}
