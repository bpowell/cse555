#include <iostream>
#include <boost/multi_array.hpp>

#include "global.h"
#include "StructElement.h"
#include "Map.h"
#include "Morphological.h"

#include "Game.h"
#include "Screen.h"

int main(void) {
    StructElement_ptr structelement(new StructElement(11));
    Map_ptr map(new Map(WIDTH, HEIGHT, 45, structelement));
    Morphological_ptr morph(new Morphological(map));
    map->print();
    std::cout << std::endl;
    map->printview();
    std::cout << std::endl;
    structelement->print_se();
    std::cout << std::endl << std::endl;
    morph->closing();
    map->printview();

    dngine::Game_ptr game(new dngine::Game("cse555", 800, 600));
    dngine::Screen_ptr screen = game.get()->create_screen();
    game.get()->set_screen(screen);

    map_index i = 0;
    map_index j = 0;
    std::cout << std::endl;
    int add = structelement->se_size / 2;
    for(i=add; i<50+add; i++){
        for(j=add; j<50+add; j++){
            SDL_Rect *loc = new SDL_Rect(); loc->x=j*10; loc->y=i*10; loc->w=loc->h=10;
            SDL_Rect *size = new SDL_Rect(); size->x=size->y=0; size->w=size->h=80;
            screen.get()->add_sprite(dngine::Sprite_ptr(new dngine::Sprite(screen.get()->get_renderer(), "tileset.png", loc, size, map->map_layout[i][j], 0)));
        }
    }

    while (1) {
        SDL_Event e;
        if ( SDL_PollEvent(&e) ) {
            if (e.type == SDL_QUIT)
                break;
            else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
                break;
        }

        game->render();

    }
    return 0;
}
