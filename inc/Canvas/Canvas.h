#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <SDL_render.h>
#include <SDL2/SDL.h>

#include "Buffer.inl" //frame + depth buffers

namespace Graphics
{
    class SDLCanvas
    {
    public:
        SDLCanvas() = delete;

        static SDL_Renderer *get_renderer();

        static void set_renderer(SDL_Renderer *new_renderer);

        static void set_color(int r, int g, int b, int a);

        static void set_pixel(int x, int y);

        static void draw_line(int x1, int y1, int x2, int y2);

        static void set_window_size(int w, int h);

        //deprecated?
        static void set_viewport(int x, int y);

        static void clear(int r, int g, int b, int a); 


    protected:
        static SDL_Renderer *renderer;
        static int win_width, win_height, viewpoint_x, viewpoint_y;
    };
}

//buffer kadra budet v drawmanager'e. On budet upravlat etim
#include "Canvas.hpp"


#endif

