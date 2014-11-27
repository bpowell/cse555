#include <iostream>

#include "Game.h"

namespace dngine{
	Game::Game(std::string name, int width, int height){
		if(SDL_Init(SDL_INIT_VIDEO) < 0){
			std::cout << "Cannot load SDL\n";
			exit(-1);
		}

		SDL_Window *w = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
        window.reset(w, SDL_DestroyWindow);
	}

	Game::~Game(){
	}

	SDL_Window_ptr Game::get_window(){
		return window;
	}

	Screen_ptr Game::create_screen(){
		SDL_Renderer_ptr r(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
		Screen_ptr s(new Screen(r));

		return s;
	}

	void Game::render(){
	}
}
