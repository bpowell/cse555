#include "Sprite.h"

namespace dngine{
	Sprite::Sprite(SDL_Renderer_ptr r, std::string fname){
		renderer = r;
		filename = fname;
		image = load_image(r.get());
	}

	Sprite::~Sprite(){
		SDL_DestroyTexture(image);
	}

	SDL_Texture* Sprite::get_texture(){
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

	SDL_Texture* Sprite::load_image(SDL_Renderer *r){
		SDL_Texture *i = IMG_LoadTexture(r, filename.c_str());
		return i;
	}

	void Sprite::render(){
		SDL_RenderCopy(renderer.get(), image, NULL, location);
	}
}
