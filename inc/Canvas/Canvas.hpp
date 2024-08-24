#include "Buffer.inl"
#include "Canvas.h"

using namespace Graphics;

SDL_Renderer* SDLCanvas::renderer = nullptr;


SDL_Renderer* SDLCanvas::get_renderer()
{
    return renderer;
}

void SDLCanvas::set_renderer(SDL_Renderer *new_renderer)
{
    renderer = new_renderer;
}

void SDLCanvas::set_color(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void SDLCanvas::set_pixel(int x, int y)
{
    SDL_RenderDrawPoint(renderer, x, y);
}

void SDLCanvas::clear(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}


void SDLCanvas::draw_line(int x1, int y1, int x2, int y2)
{
    int x = x1;
    int y = y1;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x2 > x1 ? 1 : -1;
    int sy = y2 > y1 ? 1 : -1;
    bool swap = false;
    if (dy > dx)
    {
        swap = true;
        int t = dx;
        dx = dy;
        dy = t;
    }

    int dy2 = 2 * dy;
    int dx2 = 2 * dx;
    int error = dy2 - dx;

    for (int i = 0; i < dx; i++)
    {
        SDL_RenderDrawPoint(renderer, x, y);
        while (error >= 0)
        {
            if (swap)
                x += sx;
            else
                y += sy;
            error -= dx2;
        }
        error += dy2;
        if (swap)
            y += sy;
        else
            x += sx;
    }
}