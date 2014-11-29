#include <iostream>
#include <list>
#include <thread>

#include "global.h"
#include "StructElement.h"
#include "Map.h"
#include "Morphological.h"

#include "Display.h"
#include "Timer.h"

bool running;

void render(std::list<Display_ptr> displays) {
    dngine::Timer timer;
    while(running) {
        timer.start();

		std::list<Display_ptr>::iterator it;
		for(it=displays.begin(); it!=displays.end(); ++it){
			(*it)->render();
		}

        if(timer.get_ticks()<(1000/30))
            SDL_Delay((1000/30)-timer.get_ticks());
    }

    std::cout << "stopping rendering\n";
}

int main(void) {
    std::list<Display_ptr> displays;
    StructElement_ptr structelement(new StructElement(11));
    Map_ptr map(new Map(WIDTH, HEIGHT, 45, structelement));
    Morphological_ptr morph(new Morphological(map));
    displays.push_back(Display_ptr(new Display("Map with random rooms", map->map_layout, 610, 640)));
    displays.push_back(Display_ptr(new Display("Map with random rooms after dilation", morph->dilation(), 610, 640)));
    morph->closing();
    displays.push_back(Display_ptr(new Display("Map after closing", map->map_layout, 610, 640)));

    running = true;
    std::thread thread_render(render, displays);

    while(1) {
        SDL_Event e;
        if ( SDL_PollEvent(&e) ) {
            if (e.type == SDL_QUIT)
                break;
            else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
                break;
        }
    }
    std::cout << "done with while loop\n";
    running = false;
    thread_render.join();

    return 0;
}
