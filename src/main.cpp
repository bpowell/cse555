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
	SDL_Rect size; size.x=size.y=0; size.w=size.h=40;
	dngine::SpriteSheet_ptr sheet(new dngine::SpriteSheet(screen->get_renderer(), "toon.png", &size, 4, 0));
	sheet.get()->set_clip(3,0);
	screen.get()->add_sprite("two", sheet);
	SDL_Rect loc; loc.x=loc.y=0; loc.h=loc.w=140;
	sheet.get()->set_location(&loc);

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
