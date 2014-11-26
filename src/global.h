#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <boost/multi_array.hpp>
#include <SDL2/SDL.h>

#include <memory>

typedef std::shared_ptr<SDL_Window> SDL_Window_ptr;
typedef std::shared_ptr<SDL_Renderer> SDL_Renderer_ptr;

typedef boost::multi_array<int, 2> map_array;
typedef map_array::index map_index;
typedef boost::multi_array_types::index_range range;

#define WIDTH 50
#define HEIGHT 50
#define MAX_ROOM_SIZE 5

#endif
