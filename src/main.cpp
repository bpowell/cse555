#include <iostream>
#include <boost/multi_array.hpp>
#include <random>

typedef boost::multi_array<int, 2> map_array;
typedef map_array::index map_index;
typedef boost::multi_array_types::index_range range;

#define WIDTH 50
#define HEIGHT 50
#define MAX_ROOM_SIZE 5

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

        Map(int width, int height, int num_rooms, int se_size) : width(width), height(height), num_rooms(num_rooms), se_size(se_size) {
            int padding = se_size / (int) 2;
            map_layout.resize(boost::extents[width+padding][height+padding]);
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

            int padding = se_size / (int) 2;
            map_array::array_view<2>::type map_view = map_layout[boost::indices[range(padding,width)][range(padding,height)]];

            for(i=x; i<room_size+x; i++){
                for(j=y; j<room_size+y; j++){
                    map_view[i][j] = 1;
                }
            }
        }

        void print() {
            map_index i = 0;
            map_index j = 0;

            for(i=0; i<width; i++){
                for(j=0; j<height; j++){
                    std::cout << map_layout[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }

        void printview() {
            int padding = se_size / (int) 2;
            map_array::array_view<2>::type map_view = map_layout[boost::indices[range(padding,width)][range(padding,height)]];

            map_index i = 0;
            map_index j = 0;

            for(i=0; i<width-padding; i++){
                for(j=0; j<height-padding; j++){
                    std::cout << map_view[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
};

int main(void) {
    Map *map = new Map(WIDTH, HEIGHT, 5, 5);
    map->print();
    std::cout << std::endl;
    map->printview();
    std::cout << std::endl;
    map->print_se();
    return 0;
}
