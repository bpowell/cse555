#include <iostream>
#include <boost/multi_array.hpp>

#include "global.h"
#include "StructElement.h"
#include "Map.h"
#include "Morphological.h"

int main(void) {
    StructElement *structelement = new StructElement(11);
    Map *map = new Map(WIDTH, HEIGHT, 45, structelement);
    Morphological *morph = new Morphological(map);
    map->print();
    std::cout << std::endl;
    map->printview();
    std::cout << std::endl;
    structelement->print_se();
    std::cout << std::endl << std::endl;
    morph->closing();
    map->printview();
    return 0;
}
