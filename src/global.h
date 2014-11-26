#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <SDL2/SDL.h>

#include <memory>

typedef std::shared_ptr<SDL_Window> SDL_Window_ptr;
typedef std::shared_ptr<SDL_Renderer> SDL_Renderer_ptr;

#endif
