#include <iostream>
#include <boost/multi_array.hpp>
#include <random>

#include "global.h"
#include "StructElement.h"

#define WIDTH 50
#define HEIGHT 50
#define MAX_ROOM_SIZE 5

bool operator==(const map_array::array_view<2>::type &lhs, map_array &rhs) {
    unsigned int i = 0;
    unsigned int j = 0;

    for(; i<lhs.shape()[0]; i++){
        for(j=0; j<lhs.shape()[1]; j++){
            if(lhs[i][j]!=rhs[i][j]){
                return false;
            }
        }
    }

    return true;
}

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
        StructElement *structelement;

        Map(int width, int height, int num_rooms, StructElement *structelement) : width(width), height(height), num_rooms(num_rooms), structelement(structelement) {
            padding = structelement->se_size / (int) 2;
            width_padding = width + 2*padding;
            height_padding = height + 2*padding;

            map_layout.resize(boost::extents[width_padding][height_padding]);

            int i;
            for(i=0; i<num_rooms; i++){
                random_room();
            }
        }

        void random_room() {
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

        void print() {
            map_index i = 0;
            map_index j = 0;

            for(i=0; i<width_padding; i++){
                for(j=0; j<height_padding; j++){
                    std::cout << map_layout[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }

        void printview() {
            map_index i = 0;
            map_index j = 0;

            for(i=padding; i<width+2; i++){
                for(j=padding; j<height+2; j++){
                    std::cout << map_layout[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
};

class Morphological {
    public:
        Map *map;
        StructElement *element;

        Morphological(Map *map, StructElement *element) : map(map), element(element) {}
        Morphological(Map *map) : map(map), element(map->structelement) {}

        void dilation() {
            int padding = map->padding;
            int width = map->width;
            int height = map->height;
            int width_padding = map->width_padding;
            int height_padding = map->height_padding;

            map_array dilated;
            dilated.resize(boost::extents[width_padding][height_padding]);

            map_index i = 0;
            map_index j = 0;
            for(i=0; i<element->se_size; i++){
                for(j=0; j<element->se_size; j++){
                    element->struct_element[i][j] = 0;
                }
            }

            for(i=padding; i<width+padding; i++){
                for(j=padding; j<height+padding; j++){
                    if(!compare(i,j)){
                        dilated[i+1][j+1] = 1;
                    }
                }
            }

            map->map_layout = dilated;
        }

        void erosion() {
            int padding = map->padding;
            int width = map->width;
            int height = map->height;
            int width_padding = map->width_padding;
            int height_padding = map->height_padding;

            map_array eroded;
            eroded.resize(boost::extents[width_padding][height_padding]);

            map_index i = 0;
            map_index j = 0;
            for(i=0; i<element->se_size; i++){
                for(j=0; j<element->se_size; j++){
                    element->struct_element[i][j] = 1;
                }
            }

            for(i=padding; i<width+padding; i++){
                for(j=padding; j<height+padding; j++){
                    if(compare(i,j)){
                        eroded[i+1][j+1] = 1;
                    }
                }
            }

            map->map_layout = eroded;
        }

        bool compare(int x, int y) {
            int padding = map->padding;
            map_array::array_view<2>::type view = map->map_layout[boost::indices[range(x-padding,x+padding+1)][range(y-padding,y+padding+1)]];
            return (view==element->struct_element);
        }

        void closing() {
            dilation();
            erosion();
        }

        void opening() {
            erosion();
            dilation();
        }
};

int main(void) {
    StructElement *structelement = new StructElement(5);
    Map *map = new Map(WIDTH, HEIGHT, 45, structelement);
    Morphological *morph = new Morphological(map);
    map->print();
    std::cout << std::endl;
    map->printview();
    std::cout << std::endl;
    structelement->print_se();
    std::cout << std::endl << std::endl;
    morph->opening();
    map->printview();
    return 0;
}
