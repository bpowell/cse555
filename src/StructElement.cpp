#include <iostream>

#include "global.h"
#include "StructElement.h"

StructElement::StructElement(int se_size) : se_size(se_size) {
    struct_element.resize(boost::extents[se_size][se_size]);
}

void StructElement::print_se() {
   map_index i = 0;
   map_index j = 0;

   for(i=0; i<se_size; i++){
       for(j=0; j<se_size; j++){
           std::cout << struct_element[i][j] << " ";
       }
       std::cout << std::endl;
   }
}
