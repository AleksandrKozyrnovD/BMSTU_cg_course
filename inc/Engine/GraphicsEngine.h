#ifndef __GRAPHICSENGINE_H__
#define __GRAPHICSENGINE_H__

#include <SDL_render.h>
#include <SDL2/SDL.h>
#include "ModelType/Facet.h"

namespace Engine
{
    class GraphicsEngineSDL
    {
    public:
        GraphicsEngineSDL() = delete;

        static SDL_Renderer *get_renderer();

        static void set_renderer(SDL_Renderer *new_renderer);

        static void set_color(int r, int g, int b, int a);

        static void draw_point(int x, int y);

        static void draw_line(int x1, int y1, int x2, int y2);

        static void draw_circle(int x, int y, int radius);

        static void draw_ellipse(int x, int y, int radiusX, int radiusY);

        static void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3);

        static void rasterize_facet(const Facet& facet);

        static void clear(int r, int g, int b, int a); 
    protected:
        static SDL_Renderer *renderer;
    };
}

#endif

