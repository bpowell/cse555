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

	void Game::render(){
	}
}
