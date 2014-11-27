#include <iostream>
#include <boost/multi_array.hpp>

#include "Morphological.h"

Morphological::Morphological(Map *map, StructElement_ptr element) : map(map), element(element) {}
Morphological::Morphological(Map *map) : map(map), element(map->structelement) {}

void Morphological::dilation() {
    int padding = map->padding;
    int width = map->width;
    int height = map->height;
    int width_padding = map->width_padding;
    int height_padding = map->height_padding;

    map_array dilated;
    dilated.resize(boost::extents[width_padding][height_padding]);

    map_index i = 0;
    map_index j = 0;
    for(i=0; i<element.get()->se_size; i++){
        for(j=0; j<element.get()->se_size; j++){
            element.get()->struct_element[i][j] = 0;
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

void Morphological::erosion() {
    int padding = map->padding;
    int width = map->width;
    int height = map->height;
    int width_padding = map->width_padding;
    int height_padding = map->height_padding;

    map_array eroded;
    eroded.resize(boost::extents[width_padding][height_padding]);

    map_index i = 0;
    map_index j = 0;
    for(i=0; i<element.get()->se_size; i++){
        for(j=0; j<element.get()->se_size; j++){
            element.get()->struct_element[i][j] = 1;
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

bool Morphological::compare(int x, int y) {
    int padding = map->padding;
    map_array::array_view<2>::type view = map->map_layout[boost::indices[range(x-padding,x+padding+1)][range(y-padding,y+padding+1)]];
    return (view==element.get()->struct_element);
}

void Morphological::closing() {
    dilation();
    erosion();
}

void Morphological::opening() {
    erosion();
    dilation();
}

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
