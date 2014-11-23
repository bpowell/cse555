#include <iostream>
#include <boost/multi_array.hpp>
#include <random>

typedef boost::multi_array<int, 2> map_array;
typedef map_array::index map_index;
typedef boost::multi_array_types::index_range range;

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
        //the struct element used for morphological processing
        map_array struct_element;

        //width and height of the map view
        int width;
        int height;

        //number of rooms to be randomly created
        int num_rooms;

        //size of the struct element
        int se_size;

        //padding of struct element for map_layout
        int padding;

        //width and height with padding
        int width_padding;
        int height_padding;

        Map(int width, int height, int num_rooms, int se_size) : width(width), height(height), num_rooms(num_rooms), se_size(se_size) {
            padding = se_size / (int) 2;
            width_padding = width + 2*padding;
            height_padding = height + 2*padding;

            map_layout.resize(boost::extents[width_padding][height_padding]);
            struct_element.resize(boost::extents[se_size][se_size]);

            int i;
            for(i=0; i<num_rooms; i++){
                random_room();
            }
        }

        void print_se() {
            map_index i = 0;
            map_index j = 0;

            for(i=0; i<se_size; i++){
                for(j=0; j<se_size; j++){
                    std::cout << struct_element[i][j] << " ";
                }
                std::cout << std::endl;
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

        bool compare(int x, int y) {
            map_array::array_view<2>::type view = map_layout[boost::indices[range(x-padding,x+padding+1)][range(y-padding,y+padding+1)]];
            return (view==struct_element);
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

        void dilation() {
            map_array dilated;
            dilated.resize(boost::extents[width_padding][height_padding]);

            map_index i = 0;
            map_index j = 0;
            for(i=0; i<se_size; i++){
                for(j=0; j<se_size; j++){
                    struct_element[i][j] = 0;
                }
            }

            for(i=padding; i<width+padding; i++){
                for(j=padding; j<height+padding; j++){
                    if(!compare(i,j)){
                        dilated[i+1][j+1] = 1;
                    }
                }
            }

            map_layout = dilated;
        }

        void erosion() {
            map_array eroded;
            eroded.resize(boost::extents[width_padding][height_padding]);

            map_index i = 0;
            map_index j = 0;
            for(i=0; i<se_size; i++){
                for(j=0; j<se_size; j++){
                    struct_element[i][j] = 1;
                }
            }

            for(i=padding; i<width+padding; i++){
                for(j=padding; j<height+padding; j++){
                    if(compare(i,j)){
                        eroded[i+1][j+1] = 1;
                    }
                }
            }

            map_layout = eroded;
        }
};

int main(void) {
    Map *map = new Map(WIDTH, HEIGHT, 5, 3);
    map->print();
    std::cout << std::endl;
    map->printview();
    std::cout << std::endl;
    map->print_se();
    std::cout << std::endl << std::endl;
    map->erosion();
    map->printview();
    return 0;
}
