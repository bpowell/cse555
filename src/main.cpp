#include <iostream>
#include <boost/multi_array.hpp>

#include "global.h"
#include "StructElement.h"
#include "Map.h"
#include "Morphological.h"

#include "Display.h"
#include "Timer.h"

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

    dngine::Timer timer;
    Display *display1 = new Display("cse555", map->map_layout, 610, 640);

    while (1) {
        timer.start();
        SDL_Event e;
        if ( SDL_PollEvent(&e) ) {
            if (e.type == SDL_QUIT)
                break;
            else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
                break;
        }

        display1->render();
        if(timer.get_ticks()<(1000/30))
            SDL_Delay((1000/30)-timer.get_ticks());

    }
    return 0;
}
