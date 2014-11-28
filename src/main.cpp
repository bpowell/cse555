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
    char c = 65;
    for(i=0; i<1; i++){
        for(j=0; j<2; j++){
            std::string name = "tile";
            name.append(1,c);
            c++;
            SDL_Rect loc; loc.x=loc.y=20*i; loc.h=loc.w=20+(j*20);
            SDL_Rect size; size.x=size.y=0; size.w=size.h=40;
            //std::cout << loc.x << " " << loc.y << " " << loc.w << " " << loc.h << std::endl;
            //std::cout << size.x << " " << size.y << " " << size.w << " " << size.h << std::endl;
            screen.get()->add_sprite(name, dngine::Sprite_ptr(new dngine::Sprite(screen.get()->get_renderer(), "toon.png", &loc, &size, 1, 0)));
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
