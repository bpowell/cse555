#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <string>

#include "global.h"
#include "Game.h"
#include "Screen.h"

class Display {
    public:
        std::string name;
        map_array map;
        int width;
        int height;
        dngine::Game_ptr game;

        Display(std::string name, map_array map, int width, int height);
        void render();
};

#endif
