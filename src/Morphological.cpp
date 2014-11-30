#include <iostream>
#include <boost/multi_array.hpp>

#include "Morphological.h"

Morphological::Morphological(Map_ptr map, StructElement_ptr element) :
    map(map), element(element) {}
Morphological::Morphological(Map_ptr map) :
    map(map), element(map.get()->structelement) {}

map_array Morphological::dilation() {
    int padding = map.get()->padding;
    int width = map.get()->width;
    int height = map.get()->height;
    int width_padding = map.get()->width_padding;
    int height_padding = map.get()->height_padding;

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

    return dilated;
}

map_array Morphological::erosion() {
    int padding = map.get()->padding;
    int width = map.get()->width;
    int height = map.get()->height;
    int width_padding = map.get()->width_padding;
    int height_padding = map.get()->height_padding;

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

    return eroded;
}

bool Morphological::compare(int x, int y) {
    int padding = map.get()->padding;
    map_array::array_view<2>::type view =
        map.get()->map_layout
        [boost::indices[range(x-padding,x+padding+1)][range(y-padding,y+padding+1)]];
    return (view==element.get()->struct_element);
}

void Morphological::closing() {
    map->map_layout = dilation();
    map->map_layout = erosion();
}

void Morphological::opening() {
    map->map_layout = erosion();
    map->map_layout = dilation();
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
