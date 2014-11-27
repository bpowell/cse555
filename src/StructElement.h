#ifndef _STRUCT_ELEMENT_H_
#define _STRUCT_ELEMENT_H_

#include <boost/multi_array.hpp>

#include "global.h"

class StructElement {
    public:
        //the struct element used for processing
        map_array struct_element;

        //size of the struct element
        int se_size;

        StructElement(int se_size);

        void print_se();
};

typedef std::shared_ptr<StructElement> StructElement_ptr;
#endif
