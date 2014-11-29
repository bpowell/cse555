#include <iostream>
#include <list>

#include "global.h"
#include "StructElement.h"
#include "Map.h"
#include "Morphological.h"

#include "Display.h"
#include "Timer.h"

int main(void) {
    std::list<Display_ptr> displays;

    StructElement_ptr structelement(new StructElement(11));
    Map_ptr map(new Map(WIDTH, HEIGHT, 45, structelement));
    Morphological_ptr morph(new Morphological(map));
    displays.push_back(Display_ptr(new Display("Map with random rooms", map->map_layout, 610, 640)));
    displays.push_back(Display_ptr(new Display("Map with random rooms after dilation", morph->dilation(), 610, 640)));
    morph->closing();
    displays.push_back(Display_ptr(new Display("Map after closing", map->map_layout, 610, 640)));

    dngine::Timer timer;

    while (1) {
        timer.start();
        SDL_Event e;
        if ( SDL_PollEvent(&e) ) {
            if (e.type == SDL_QUIT)
                break;
            else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
                break;
        }

		std::list<Display_ptr>::iterator it;
		for(it=displays.begin(); it!=displays.end(); ++it){
			(*it)->render();
		}

        if(timer.get_ticks()<(1000/30))
            SDL_Delay((1000/30)-timer.get_ticks());

    }
    return 0;
}
