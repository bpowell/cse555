#include <iostream>
#include <boost/multi_array.hpp>
#include <random>

typedef boost::multi_array<int, 2> map_array;
typedef map_array::index map_index;


#define WIDTH 50
#define HEIGHT 50

#define MAX_ROOM_SIZE 5

map_array random_room(map_array map_layout) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis1(0, WIDTH);
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

    return map_layout;
}

int main(void) {
    map_array map_layout;
    map_layout.resize(boost::extents[WIDTH][HEIGHT]);
    map_layout = random_room(map_layout);

    map_index i = 0;
    map_index j = 0;

    for(i=0; i<WIDTH; i++){
        for(j=0; j<HEIGHT; j++){
            std::cout << map_layout[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
