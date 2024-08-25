#include "Buffer.inl"
#include "Canvas.h"
#include "DrawManager.h"
#include "SceneManager.h"

#include "DrawVisitor.h"
#include "ZMapper.h"
#include "LightCaster.h"
#include "glm/ext/matrix_projection.hpp"


using namespace ControlSystem;

int Buffer::width = 1280;
int Buffer::height = 720;

bool DrawManager::do_we_draw = true;

std::vector<std::vector<float>> Buffer::original_buffer
= std::vector<std::vector<float>>(height, std::vector<float>(width, 1.0f));

std::vector<std::vector<float>> Buffer::depth_buffer = original_buffer;
std::vector<std::vector<float>> Buffer::light_depth_buffer = original_buffer;


std::vector<std::vector<uint32_t>> Buffer::original_frame_buffer
= std::vector<std::vector<uint32_t>>(height, std::vector<uint32_t>(width, 0));

std::vector<std::vector<uint32_t>> Buffer::frame_buffer = original_frame_buffer;
std::vector<std::vector<uint32_t>> Buffer::light_frame_buffer = original_frame_buffer;



void DrawManager::set_window_size(int w, int h)
{
    Buffer::width = w;
    Buffer::height = h;

    Buffer::original_buffer
    = std::vector<std::vector<float>>(Buffer::height, std::vector<float>(Buffer::width, 1.0f));
    Buffer::depth_buffer = Buffer::original_buffer;

    Buffer::original_frame_buffer
    = std::vector<std::vector<uint32_t>>(Buffer::height, std::vector<uint32_t>(Buffer::width, 0x00000000));
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
            int r = (color & 0xFF000000) >> 24;
            int g = (color & 0x00FF0000) >> 16;
            int b = (color & 0x0000FF00) >> 8;
            int a = color & 0x000000FF;

            r /= (Buffer::depth_buffer[y][x] + 2.5f);
            g /= (Buffer::depth_buffer[y][x] + 2.5f);
            b /= (Buffer::depth_buffer[y][x] + 2.5f);

            Graphics::SDLCanvas::set_color(r, g, b, a);
            Graphics::SDLCanvas::set_pixel(x, y);
        }
    }


    return;
}

void DrawManager::draw_scene()
{
    if (DrawManager::do_we_draw)
    {
        std::cout << "Drawing!" << std::endl;
        std::shared_ptr<Camera> camera = ControlSystem::SceneManager::get_main_camera();

        auto objects = ControlSystem::SceneManager::get_objects();
        auto lights = ControlSystem::SceneManager::get_lights();
        Buffer::frame_buffer = Buffer::original_frame_buffer;
        Buffer::depth_buffer = Buffer::original_buffer;

        //make depth buffer from camera view point
        std::shared_ptr<AbstractVisitor> depth_visitor = std::make_shared<ZMapper>(camera);
        for (auto &obj : objects)
        {
            obj->accept(depth_visitor);
        }

        //what each light see and then what camera see?
        //for every light source cast shadow from it
        for (auto& light : lights)
        {
            std::shared_ptr<LightCaster> caster = std::make_shared<LightCaster>(camera, light);
            ControlSystem::Buffer::light_depth_buffer = ControlSystem::Buffer::original_buffer; //reset depth buffer
            ControlSystem::Buffer::light_frame_buffer = ControlSystem::Buffer::original_frame_buffer; //reset frame buffer
            for (auto &obj : objects)
            {
                obj->accept(caster);
            }
            DrawManager::process_from_viewpoint(light, camera, glm::mat4(1.0f));
        }
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

            // r /= (Buffer::depth_buffer[y][x] + 2.5f);
            // g /= (Buffer::depth_buffer[y][x] + 2.5f);
            // b /= (Buffer::depth_buffer[y][x] + 2.5f);

            Graphics::SDLCanvas::set_color(r, g, b, a);
            Graphics::SDLCanvas::set_pixel(x, y);
        }
    }


    return;
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
    glm::vec4 viewport(0.0f, 0.0f, w, h);

    for (int y = 0; y < 720; ++y)
    {
        for (int x = 0; x < 1280; ++x)
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
                
                // std::cout << "World: " << lightdepthbufferpoint.x << " " << lightdepthbufferpoint.y << " " << lightdepthbufferpoint.z << std::endl;

                //now to get the point in light coordinates
                lightdepthbufferpoint = glm::vec3(
                    glm::project(lightdepthbufferpoint, transform, light_proj, viewport));
                
                // std::cout << "Light: " << lightdepthbufferpoint.x << " " << lightdepthbufferpoint.y << " " << lightdepthbufferpoint.z << std::endl;


                int x2 = round(lightdepthbufferpoint.x);
                int y2 = round(lightdepthbufferpoint.y);
                float z2 = lightdepthbufferpoint.z;

                if (x2 >= 0 && x2 < 1280 && y2 >= 0 && y2 < 720 && z2 > 0)
                {
                    //if z is not far from shadowmap's z
                    if (fabs(ControlSystem::Buffer::light_depth_buffer[y2][x2] - z2) < 0.0025f)
                    {
                        Buffer::frame_buffer[y][x] = Buffer::light_frame_buffer[y2][x2];
                    }
                }
            }
        }
    }
}