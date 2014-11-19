#include <iostream>
#include <boost/multi_array.hpp>
#include <random>

typedef boost::multi_array<int, 2> map_array;
typedef map_array::index map_index;

#define WIDTH 50
#define HEIGHT 50
#define MAX_ROOM_SIZE 5

class Map {
    public:
        map_array map_layout;
        map_array struct_element;
        int width;
        int height;
        int num_rooms;
        int se_size;

        Map(int width, int height, int num_rooms, int se_size) : width(width), height(height), num_rooms(num_rooms), se_size(se_size) {
            map_layout.resize(boost::extents[width][height]);
            int i;
            for(i=0; i<num_rooms; i++){
                random_room();
            }

            struct_element.resize(boost::extents[se_size][se_size]);
            struct_element[(int)se_size/2][(int)se_size/2] = 1;
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

        void print() {
            map_index i = 0;
            map_index j = 0;

            for(i=0; i<WIDTH; i++){
                for(j=0; j<HEIGHT; j++){
                    std::cout << map_layout[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
};

int main(void) {
    Map *map = new Map(WIDTH, HEIGHT, 5, 5);
    map->print();
    std::cout << std::endl;
    map->print_se();
    return 0;
}
