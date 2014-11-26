#ifndef _MORPHOLOGICAL_H_
#define _MORPHOLOGICAL_H_

#include "global.h"
#include "StructElement.h"
#include "Map.h"

class Morphological {
    public:
        Map *map;
        StructElement *element;

        Morphological(Map *map, StructElement *element);
        Morphological(Map *map);

        void dilation();
        void erosion();
        bool compare(int x, int y);
        void closing();
        void opening();

};

bool operator==(const map_array::array_view<2>::type &lhs, map_array &rhs);
#endif
