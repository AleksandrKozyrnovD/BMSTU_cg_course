#include "Canvas.h"
#include "DrawManager.h"
#include "SceneManager.h"

#include "DrawVisitor.h"


using namespace ControlSystem;

int Buffer::width = 1280;
int Buffer::height = 720;

std::vector<std::vector<float>> Buffer::original_buffer
= std::vector<std::vector<float>>(height, std::vector<float>(width, 1e38f));

std::vector<std::vector<float>> Buffer::depth_buffer = original_buffer;

std::vector<std::vector<uint32_t>> Buffer::original_frame_buffer
= std::vector<std::vector<uint32_t>>(height, std::vector<uint32_t>(width, Color::GRAY));

std::vector<std::vector<uint32_t>> Buffer::frame_buffer = original_frame_buffer;


void DrawManager::set_window_size(int w, int h)
{
    Buffer::width = w;
    Buffer::height = h;

    Buffer::original_buffer
    = std::vector<std::vector<float>>(Buffer::height, std::vector<float>(Buffer::width, 0.0f));
    Buffer::depth_buffer = Buffer::original_buffer;

    Buffer::original_frame_buffer
    = std::vector<std::vector<uint32_t>>(Buffer::height, std::vector<uint32_t>(Buffer::width, 0x777777ff));
    Buffer::frame_buffer = Buffer::original_frame_buffer;
}

void DrawManager::draw_scene_no_lights()
{
    std::shared_ptr<Camera> camera = ControlSystem::SceneManager::get_main_camera();

    auto objects = ControlSystem::SceneManager::get_objects();
    std::shared_ptr<AbstractVisitor> visitor = std::make_shared<DrawVisitor>(camera);

    Buffer::frame_buffer = Buffer::original_frame_buffer;
    Buffer::depth_buffer = Buffer::original_buffer;

    for (auto &obj : objects)
    {
        obj->accept(visitor);
    }

    //apply frame_buffer to screen
    for (int y = 0; y < Buffer::height; ++y)
    {
        for (int x = 0; x < Buffer::width; ++x)
        {
            //getting ARGB8888 color
            uint32_t color = Buffer::frame_buffer[y][x];
            int r = color & 0xFF;
            int g = (color >> 8) & 0xFF;
            int b = (color >> 16) & 0xFF;
            int a = (color >> 24) & 0xFF;

            Graphics::SDLCanvas::set_color(r, g, b, a);
            Graphics::SDLCanvas::set_pixel(x, y);
        }
    }


    return;
}

void DrawManager::draw_scene()
{
    return;
}