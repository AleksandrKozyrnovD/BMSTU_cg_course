#include "Canvas.h"
#include <memory>

#include "SceneManager.h"
// #include "ZMapper.h"
#include "normalzbuffer/NewDrawVisitor.h"
// #include "LightCaster.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_projection.hpp"

using namespace ControlSystem;

int Buffer::width = 1940;
int Buffer::height = 1200;
int Buffer::shadow_res = 1500;

bool DrawManager::do_we_draw = true;

std::vector<std::vector<float>> Buffer::original_buffer
= std::vector<std::vector<float>>(Buffer::height, std::vector<float>(Buffer::width, 0.0f));

std::vector<std::vector<uint32_t>> Buffer::original_frame_buffer
= std::vector<std::vector<uint32_t>>(Buffer::height, std::vector<uint32_t>(Buffer::width, 0x4444FFDD)); //bluish color



std::vector<std::vector<float>> Buffer::depth_buffer = original_buffer;
std::vector<std::vector<uint32_t>> Buffer::frame_buffer = original_frame_buffer;

std::vector<std::vector<float>> Buffer::original_light_depth
= std::vector<std::vector<float>>(Buffer::shadow_res, std::vector<float>(Buffer::shadow_res, 1.0f));

std::vector<std::vector<uint32_t>> Buffer::original_light_frame
= std::vector<std::vector<uint32_t>>(Buffer::shadow_res, std::vector<uint32_t>(Buffer::shadow_res, 0));



std::vector<std::vector<float>> Buffer::light_depth_buffer = original_light_depth;
std::vector<std::vector<uint32_t>> Buffer::light_frame_buffer = original_light_frame;


void DrawManager::set_window_size(int w, int h, Window::Settings& settings)
{
    Buffer::width = w;
    Buffer::height = h;

    settings.width = w;
    settings.height = h;
}

void DrawManager::draw_scene_no_lights()
{
    // if (DrawManager::do_we_draw)
    // {
    //     std::shared_ptr<Camera> camera = ControlSystem::SceneManager::get_main_camera();

    //     auto objects = ControlSystem::SceneManager::get_drawable_objects();
    //     std::shared_ptr<AbstractVisitor> visitor = std::make_shared<DrawVisitor>(camera);

    //     Buffer::frame_buffer = Buffer::original_frame_buffer;
    //     Buffer::depth_buffer = Buffer::original_buffer;

    //     for (auto &obj : objects)
    //     {
    //         obj->accept(visitor);
    //     }
    //     DrawManager::do_we_draw = false;
    // }

    // //apply frame_buffer to screen
    // for (int y = 0; y < Buffer::height; ++y)
    // {
    //     for (int x = 0; x < Buffer::width; ++x)
    //     {
    //         //getting ARGB8888 color
    //         uint32_t color = Buffer::frame_buffer[y][x];
    //         int r = (color & 0xFF000000) >> 24;
    //         int g = (color & 0x00FF0000) >> 16;
    //         int b = (color & 0x0000FF00) >> 8;
    //         int a = color & 0x000000FF;

    //         Graphics::SDLCanvas::set_color(r, g, b, a);
    //         Graphics::SDLCanvas::set_pixel(x, y);
    //     }
    // }


    return;
}

#include <chrono>

void DrawManager::new_draw_scene()
{
    /*
    seconds with light
    12 0.4
    24 1.65
    36 1.85
    48 1.7
    60 1.76
    72 1.91
    84 2.13
    96 2.34
    108 2.41
    120 2.55
    */
    /*
    seconds without light
    12 0.14
    24 0.41
    36 0.0.42
    48 0.46
    60 0.39
    72 0.48
    84 0.5
    96 0.54
    108 0.48
    120 0.57
    */
    if (DrawManager::do_we_draw)
    {
        // auto start = std::chrono::system_clock::now();
        std::shared_ptr<Camera> camera = ControlSystem::SceneManager::get_main_camera();

        auto objects = ControlSystem::SceneManager::get_drawable_objects();
        auto lights = ControlSystem::SceneManager::get_lights();
        Buffer::frame_buffer = Buffer::original_frame_buffer;
        Buffer::depth_buffer = Buffer::original_buffer;

        for (auto& light : lights)
        {
            light->clear_shadow_buffer();
        }

        for (auto& light : lights)
        {
            std::shared_ptr<AbstractVisitor> shadower = std::make_shared<ShadowMapper>(light);
            for (auto &obj : objects)
            {
                obj->accept(shadower);
            }
        }

        std::shared_ptr<AbstractVisitor> visitor = std::make_shared<ZBufMapper>(camera);
        for (auto &obj : objects)
        {
            obj->accept(visitor);
        }

        // auto end = std::chrono::system_clock::now();
        // std::chrono::duration<float> duration = end - start;
        // std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        // std::cout << "Time rendering: " << ms.count() << std::endl;
        DrawManager::do_we_draw = false;
    }
    //apply frame_buffer to screen
    for (int y = 0; y < Buffer::height; ++y)
    {
        for (int x = 0; x < Buffer::width; ++x)
        {
            //getting ARGB8888 color
            uint32_t color = Buffer::frame_buffer[y][x];
            int r = (color & 0xFF000000) >> 24;
            int g = (color & 0x00FF0000) >> 16;
            int b = (color & 0x0000FF00) >> 8;
            int a = color & 0x000000FF;

            Graphics::SDLCanvas::set_color(r, g, b, a);
            Graphics::SDLCanvas::set_pixel(x, y);
        }
    }

    return;
}

void DrawManager::draw_scene()
{
    // if (DrawManager::do_we_draw)
    // {
    //     std::cout << "Drawing!" << std::endl;
    //     std::shared_ptr<Camera> camera = ControlSystem::SceneManager::get_main_camera();

    //     auto objects = ControlSystem::SceneManager::get_drawable_objects();
    //     auto lights = ControlSystem::SceneManager::get_lights();
    //     Buffer::frame_buffer = Buffer::original_frame_buffer;
    //     Buffer::depth_buffer = Buffer::original_buffer;

    //     //make depth buffer from camera view point
    //     std::shared_ptr<AbstractVisitor> depth_visitor = std::make_shared<ZMapper>(camera);
    //     for (auto &obj : objects)
    //     {
    //         obj->accept(depth_visitor);
    //     }

    //     //what each light see and then what camera see?
    //     //for every light source cast shadow from it
    //     for (auto& light : lights)
    //     {
    //         std::shared_ptr<LightCaster> caster = std::make_shared<LightCaster>(camera, light);
    //         for (auto &obj : objects)
    //         {
    //             ControlSystem::Buffer::light_depth_buffer = ControlSystem::Buffer::original_light_depth; //reset depth buffer
    //             ControlSystem::Buffer::light_frame_buffer = ControlSystem::Buffer::original_light_frame; //reset frame buffer
    //             obj->accept(caster);
    //             DrawManager::process_from_viewpoint(light, camera, obj->transform);
    //         }
    //     }
    //     DrawManager::do_we_draw = false;
    // }
    // //apply frame_buffer to screen
    // for (int y = 0; y < Buffer::height; ++y)
    // {
    //     for (int x = 0; x < Buffer::width; ++x)
    //     {
    //         //getting ARGB8888 color
    //         uint32_t color = Buffer::frame_buffer[y][x];
    //         int r = (color & 0xFF000000) >> 24;
    //         int g = (color & 0x00FF0000) >> 16;
    //         int b = (color & 0x0000FF00) >> 8;
    //         int a = color & 0x000000FF;

    //         Graphics::SDLCanvas::set_color(r, g, b, a);
    //         Graphics::SDLCanvas::set_pixel(x, y);
    //     }
    // }
}

void DrawManager::process_from_viewpoint(std::shared_ptr<Light>& light_source, std::shared_ptr<Camera>& camera, glm::mat4 transform)
{
    glm::mat4 camera_view = camera->get_view_matrix();
    glm::mat4 camera_perspective = camera->get_perspective_matrix();
    glm::mat4 light_view = light_source->get_view_matrix();
    glm::mat4 light_perspective = light_source->get_perspective_matrix();

    glm::mat4 camera_proj = camera_perspective * camera_view;
    glm::mat4 light_proj = light_perspective * light_view;

    int w = ControlSystem::Buffer::width;
    int h = ControlSystem::Buffer::height;
    int shadow_res = ControlSystem::Buffer::shadow_res;

    glm::vec4 viewport(0.0f, 0.0f, w, h);
    glm::vec4 shadowport(0.0f, 0.0f, shadow_res, shadow_res);

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            float z = ControlSystem::Buffer::depth_buffer[y][x];
            // std::cout << "Initial z: " << z << std::endl;
            if (fabs(z) > 1.0f) //if not infinitely far away
            {
                glm::vec3 lightdepthbufferpoint = glm::vec3(x, y, z);

                // std::cout << "Original: " << lightdepthbufferpoint.x << " " << lightdepthbufferpoint.y << " " << lightdepthbufferpoint.z << std::endl;
                
                //to get the point in world coordinates
                lightdepthbufferpoint = glm::vec3(
                    glm::unProject(lightdepthbufferpoint, transform, camera_proj, viewport));
                
                lightdepthbufferpoint = glm::vec3(
                    glm::project(lightdepthbufferpoint, transform, light_proj, shadowport));
                

                int x2 = round(lightdepthbufferpoint.x);
                int y2 = round(lightdepthbufferpoint.y);
                float z2 = lightdepthbufferpoint.z;

                if (x2 >= 0 && x2 < shadow_res && y2 >= 0 && y2 < shadow_res/* && z2 > 0*/)
                {
                    //if z is not far from shadowmap's z
                    if (fabs(ControlSystem::Buffer::light_depth_buffer[y2][x2] - z2) < 0.025f)
                    {
                        Buffer::frame_buffer[y][x] = Buffer::light_frame_buffer[y2][x2];
                    }
                    else
                    {
                        Buffer::frame_buffer[y][x] = 0x22222222;
                    }
                }
                else
                {
                    Buffer::frame_buffer[y][x] = 0x22222222;
                }
            }
        }
    }
}