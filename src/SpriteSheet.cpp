#include "Sprite.h"

namespace dngine{
	SpriteSheet::SpriteSheet(SDL_Renderer_ptr r, std::string fname, SDL_Rect *size, int x, int y)
		:Sprite(r, fname){ 
			clip_size = size;
			max_x = x;
			max_y = y;
	}

	void SpriteSheet::render(){
		SDL_Rect clip;
		clip.x = pos_x * clip_size->w;
		clip.y = pos_y * clip_size->h;
		clip.w = clip_size->w;
		clip.h = clip_size->h;

		SDL_RenderCopy(renderer.get(), image.get(), &clip, location);
	}

	void SpriteSheet::set_clip(int x, int y){
		if(x>max_x){
			pos_x = 0;
		}else{
			pos_x = x;
		}

		if(y>max_y){
			pos_y = 0;
		}else{
			pos_y = y;
		}
	}
}
