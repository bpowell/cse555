#include "Display.h"

Display::Display(std::string name, map_array map, int width, int height) :
    name(name), map(map), width(width), height(height) {
        game = dngine::Game_ptr(new dngine::Game(name, width, height));
        dngine::Screen_ptr screen = game->create_screen();
        game->set_screen(screen);

        unsigned int i;
        unsigned int j;
        for(i=0; i<map.shape()[0]; i++){
            for(j=0; j<map.shape()[1]; j++){
                SDL_Rect *loc = new SDL_Rect();
                loc->x=j*10; loc->y=i*10; loc->w=loc->h=10;
                SDL_Rect *size = new SDL_Rect();
                size->x=size->y=0; size->w=size->h=80;
                screen->add_sprite(dngine::Sprite_ptr(new dngine::Sprite(
                                screen->get_renderer(),
                                "tileset.png", loc, size,
                                map[i][j], 0)));
            }
        }
}

void Display::render() {
    game->render();
}
