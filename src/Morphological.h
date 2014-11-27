#ifndef _MORPHOLOGICAL_H_
#define _MORPHOLOGICAL_H_

#include "global.h"
#include "StructElement.h"
#include "Map.h"

class Morphological {
    public:
        Map_ptr map;
        StructElement_ptr element;

        Morphological(Map_ptr map, StructElement_ptr element);
        Morphological(Map_ptr map);

        void dilation();
        void erosion();
        bool compare(int x, int y);
        void closing();
        void opening();

};

bool operator==(const map_array::array_view<2>::type &lhs, map_array &rhs);
typedef std::shared_ptr<Morphological> Morphological_ptr;

#endif
