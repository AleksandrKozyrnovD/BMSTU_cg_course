#include "Canvas.h"
#include "DrawManager.h"
#include "SceneManager.h"

#include "DrawVisitor.h"


using namespace ControlSystem;

int Buffer::width = 1280;
int Buffer::height = 720;

std::vector<std::vector<float>> Buffer::original_buffer
= std::vector<std::vector<float>>(height, std::vector<float>(width, 0.0f));

std::vector<std::vector<float>> Buffer::depth_buffer = original_buffer;

std::vector<std::vector<size_t>> Buffer::original_frame_buffer
= std::vector<std::vector<size_t>>(height, std::vector<size_t>(width, Color::GRAY));

std::vector<std::vector<size_t>> Buffer::frame_buffer = original_frame_buffer;


void DrawManager::set_window_size(int w, int h)
{
    Buffer::width = w;
    Buffer::height = h;

    Buffer::original_buffer
    = std::vector<std::vector<float>>(Buffer::height, std::vector<float>(Buffer::width, 0.0f));
    Buffer::depth_buffer = Buffer::original_buffer;

    Buffer::original_frame_buffer
    = std::vector<std::vector<size_t>>(Buffer::height, std::vector<size_t>(Buffer::width, Color::GRAY));
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
            //getting color
            if (Buffer::frame_buffer[y][x] == Color::RED)
            {
                Graphics::SDLCanvas::set_color(255, 0, 0, 255);
            }
            else if (Buffer::frame_buffer[y][x] == Color::GREEN)
            {
                Graphics::SDLCanvas::set_color(0, 255, 0, 255);
            }
            else if (Buffer::frame_buffer[y][x] == Color::BLUE)
            {
                Graphics::SDLCanvas::set_color(0, 0, 255, 255);
            }
            else
            {
                Graphics::SDLCanvas::set_color(0, 0, 0, 255);
            }
            Graphics::SDLCanvas::set_pixel(x, y);
        }
    }


    return;
}

void DrawManager::draw_scene()
{
    return;
}