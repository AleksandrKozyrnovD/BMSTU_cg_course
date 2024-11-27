#include "AbstractObject.h"
#include "AbstractVisitor.h"
#include "Builders/SurfaceBuilder.h"
#include "LoadManager.h"
#include "Scene.h"
#include "CompositeObject.h"

#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <memory>
#include <stdio.h>

using namespace ControlSystem;


std::shared_ptr<Camera> LoadManager::load_camera(const std::string& filename)
{
    /*
    REQUIERED:
    center - (x, y, z)
    up - (x1, y1, z1)
    forward - (x2, y2, z2)
    */

    FILE *file = fopen(filename.c_str(), "r");
    if (!file)
        return nullptr;

    float x, y, z, x1, y1, z1, x2, y2, z2;
    fscanf(file, "%f %f %f %f %f %f %f %f %f",
            &x, &y, &z,
            &x1, &y1, &z1,
            &x2, &y2, &z2);

    fclose(file);
    return std::make_shared<Camera>(glm::vec3(x, y, z), glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2));
}

std::shared_ptr<Light> LoadManager::load_light(const std::string& filename)
{
    /*
    REQUIERED:
    center - (x, y, z)
    up - (x1, y1, z1)
    forward - (x2, y2, z2)
    uint32_t color
    */

    FILE *file = fopen(filename.c_str(), "r");
    if (!file)
        return nullptr;

    float x, y, z, x1, y1, z1, x2, y2, z2;
    uint32_t color;
    fscanf(file, "%f %f %f %f %f %f %f %f %f %u",
            &x, &y, &z,
            &x1, &y1, &z1,
            &x2, &y2, &z2,
            &color);

    fclose(file);
    return std::make_shared<Light>(glm::vec3(x, y, z), glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2), color);
}

std::shared_ptr<AbstractObject> LoadManager::load_composite_object(const std::string& filename)
{
    //open file and check it's valid
    if (filename.empty())
        return nullptr;
    
    std::ifstream file(filename, std::ios_base::in);

    if (!file.is_open())
        return nullptr;
    if (!file.good())
        return nullptr;
    
    std::shared_ptr<CompositeObject> composite = std::make_shared<CompositeObject>();
    //readline
    std::string line = "1";
    float dx, dy, dz,
          rx, ry, rz,
          sx, sy, sz;
    char objfile[512];
    int type;
    std::getline(file, line);
    while (line != "")
    {
        //parse
        //Format: file type dx dy dz rx ry rz sx sy sz
        //translation - dx dy dz
        //rotation - rx ry rz
        //scale - sx sy sz
        /*
        Types:
        0 - camera
        1 - object
        2 - light
        3 - composite
        */

        sscanf(line.c_str(), "%s %d %f %f %f %f %f %f %f %f %f",
               objfile, &type,
               &dx, &dy, &dz,
               &rx, &ry, &rz,
               &sx, &sy, &sz);
        
        std::shared_ptr<AbstractObject> obj;
        std::shared_ptr<Light> light;
        std::shared_ptr<Camera> camera;
        switch (type)
        {
            case 0:
                camera = LoadManager::load_camera(objfile);
                composite->add(camera);
                SceneManager::add_camera(camera);
                break;
            case 1:
                obj = LoadManager::load_from_file<SurfaceBuilder>(objfile);
                // std::cout << "Loading. Paramets:" << std::endl;
                // std::cout << "Line: " << line << std::endl;
                // printf("%s\n", line.c_str());
                // std::cout << "dx: " << dx << " " << dy << " " << dz << std::endl;
                // std::cout << "rx: " << rx << " " << ry << " " << rz << std::endl;
                // std::cout << "sx: " << sx << " " << sy << " " << sz << std::endl;
                ControlSystem::TransformManager::scale(obj, sx, sy, sz);
                ControlSystem::TransformManager::rotate(obj, rx, ry, rz);
                ControlSystem::TransformManager::move(obj, dx, dy, dz);
                composite->add(obj);
                break;
            case 2:
                light = LoadManager::load_light(objfile);
                obj = light;
                ControlSystem::TransformManager::move(obj, dx, dy, dz);
                ControlSystem::TransformManager::rotate(obj, rx, ry, rz);
                SceneManager::add_light(light);
                composite->add(obj);
                break;
            case 3:
                obj = LoadManager::load_composite_object(objfile);
                ControlSystem::TransformManager::move(obj, dx, dy, dz);
                ControlSystem::TransformManager::rotate(obj, rx, ry, rz);
                ControlSystem::TransformManager::scale(obj, sx, sy, sz);
                composite->add(obj);
                break;
        }
        std::getline(file, line);
    }
    file.close();

    return composite;
}

void LoadManager::load_scene(const std::string& filename)
{
    //open file and check it's valid
    if (filename.empty())
        return;
    
    std::ifstream file(filename, std::ios_base::in);

    if (!file.is_open())
        return;
    if (!file.good())
        return;

    //readline
    std::string line;
    float dx, dy, dz,
          rx, ry, rz,
          sx, sy, sz;
    char objfile[512];
    int type;
    std::getline(file, line);
    while (line != "")
    {
        //parse
        //Format: file type dx dy dz rx ry rz sx sy sz
        //translation - dx dy dz
        //rotation - rx ry rz
        //scale - sx sy sz
        /*
        Types:
        0 - camera
        1 - object
        2 - light
        3 - composite
        */

        if (sscanf(line.c_str(), "%s %d %f %f %f %f %f %f %f %f %f",
               objfile, &type,
               &dx, &dy, &dz,
               &rx, &ry, &rz,
               &sx, &sy, &sz) != 11)
        {
            break;
        }
        
        std::shared_ptr<AbstractObject> obj;
        std::shared_ptr<Light> light;
        std::shared_ptr<Camera> camera;
        switch (type)
        {
            case 0:
                // SceneManager::add_camera(LoadManager::load_camera(objfile));
                camera = LoadManager::load_camera(objfile);
                SceneManager::add_camera(camera);
                SceneManager::set_camera(camera);
                break;
            case 1:
                obj = LoadManager::load_from_file<SurfaceBuilder>(objfile);
                ControlSystem::TransformManager::move(obj, dx, dy, dz);
                ControlSystem::TransformManager::rotate(obj, rx, ry, rz);
                ControlSystem::TransformManager::scale(obj, sx, sy, sz);
                SceneManager::add_object(obj);
                break;
            case 2:
                light = LoadManager::load_light(objfile);
                obj = light;
                ControlSystem::TransformManager::move(obj, dx, dy, dz);
                ControlSystem::TransformManager::rotate(obj, rx, ry, rz);
                // ControlSystem::TransformManager::scale(obj, sx, sy, sz);
                SceneManager::add_light(light);
                break;
            case 3:
                obj = LoadManager::load_composite_object(objfile);
                ControlSystem::TransformManager::move(obj, dx, dy, dz);
                ControlSystem::TransformManager::rotate(obj, rx, ry, rz);
                ControlSystem::TransformManager::scale(obj, sx, sy, sz);
                ControlSystem::SceneManager::add_object(obj);
                break;
        }
        std::getline(file, line);
    }
    file.close();
}

