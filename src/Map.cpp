#include <iostream>
#include <random>
#include <boost/multi_array.hpp>

#include "Map.h"

Map::Map(int width, int height, int num_rooms, StructElement_ptr structelement) : width(width), height(height), num_rooms(num_rooms), structelement(structelement) {
    padding = structelement.get()->se_size / (int) 2;
    width_padding = width + 2*padding;
    height_padding = height + 2*padding;

    map_layout.resize(boost::extents[width_padding][height_padding]);

    int i;
    for(i=0; i<num_rooms; i++){
        random_room();
    }
}

void Map::random_room() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis1(0, width);
    std::uniform_int_distribution<> dis2(1, MAX_ROOM_SIZE);

    int x = dis1(gen);
    int y = dis1(gen);

    int room_size = dis2(gen);
    map_index i = 0;
    map_index j = 0;

    for(i=x; i<room_size+x; i++){
        for(j=y; j<room_size+y; j++){
            map_layout[i][j] = 1;
        }
    }
}

void Map::print() {
    map_index i = 0;
    map_index j = 0;

    for(i=0; i<width_padding; i++){
        for(j=0; j<height_padding; j++){
            std::cout << map_layout[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Map::printview() {
    map_index i = 0;
    map_index j = 0;

    for(i=padding; i<width+2; i++){
        for(j=padding; j<height+2; j++){
            std::cout << map_layout[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
