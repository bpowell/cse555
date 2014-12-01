#ifndef _MAP_H_
#define _MAP_H_

#include "global.h"
#include "StructElement.h"

class Map {
    public:
        //map layout with extra padding for struct element
        map_array map_layout;

        //width and height of the map view
        int width;
        int height;

        //number of rooms to be randomly created
        int num_rooms;

        //padding of struct element for map_layout
        int padding;

        //width and height with padding
        int width_padding;
        int height_padding;

        //StructElement class
        StructElement_ptr structelement;

        Map(int width, int height, int num_rooms, StructElement_ptr structelement);
        void random_room();
        void print();
        void printview();

        void border();
        void unborder();
};

typedef std::shared_ptr<Map> Map_ptr;
#endif
