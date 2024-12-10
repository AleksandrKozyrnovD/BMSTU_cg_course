#ifndef __NEW_DRAW_VISITOR_HPP__
#define __NEW_DRAW_VISITOR_HPP__


#include "NewDrawVisitor.h"

// #include <fstream>



void NewDrawVisitor::shadow_for_model(std::list<Facet>& facets, glm::mat4 transform, std::shared_ptr<Light>& light)
{
    std::array<glm::vec3, 3> points;

    glm::mat4x4 model = transform;
    glm::mat4x4 projection = light->get_perspective_matrix();
    glm::mat4x4 view = light->get_view_matrix();
    glm::vec4 viewport(0.0f, 0.0f, ControlSystem::Buffer::shadow_res, ControlSystem::Buffer::shadow_res);
    glm::mat4 proj = projection * view;

    auto& shadowMap = light->shadow_buffer;


    // std::ofstream file("shadowmap.txt");
    for (Facet& facet : facets)
    {

        glm::vec3 p0 = facet.A;
        glm::vec3 p1 = facet.B;
        glm::vec3 p2 = facet.C;


        p0 = glm::project(p0, model, proj, viewport);
        p1 = glm::project(p1, model, proj, viewport);
        p2 = glm::project(p2, model, proj, viewport);

        if (glm::isnan(p0.x) || glm::isnan(p0.y) || glm::isnan(p0.z) || glm::isnan(p1.x) || glm::isnan(p1.y) || glm::isnan(p1.z) || glm::isnan(p2.x) || glm::isnan(p2.y) || glm::isnan(p2.z))
        {
            continue;
        }
        if (p0.z < 1.0f || p1.z < 1.0f || p2.z < 1.0f)
        {
            continue;
        }

        std::array<glm::vec3, 3> transformedDots = {
            p0, p1, p2
        };

        // file << "====================" << std::endl;
        // file << "x1: " << facet.A.x << " x2: " << facet.B.x << " x3: " << facet.C.x << std::endl;
        // file << "y1: " << facet.A.y << " y2: " << facet.B.y << " y3: " << facet.C.y << std::endl;
        // file << "z1: " << facet.A.z << " z2: " << facet.B.z << " z3: " << facet.C.z << std::endl;
        // file << ">------------------<" << std::endl;
        // file << "x1: " << transformedDots[0].x << " x2: " << transformedDots[1].x << " x3: " << transformedDots[2].x << std::endl;
        // file << "y1: " << transformedDots[0].y << " y2: " << transformedDots[1].y << " y3: " << transformedDots[2].y << std::endl;
        // file << "z1: " << transformedDots[0].z << " z2: " << transformedDots[1].z << " z3: " << transformedDots[2].z << std::endl;
        // file << "====================" << std::endl;


        if (transformedDots[0].y > transformedDots[1].y)
            std::swap(transformedDots[0], transformedDots[1]);
        if (transformedDots[0].y > transformedDots[2].y)
            std::swap(transformedDots[0], transformedDots[2]);
        if (transformedDots[1].y > transformedDots[2].y)
            std::swap(transformedDots[1], transformedDots[2]);

        if (transformedDots[2].y - transformedDots[0].y <= 1)
        {
            continue;
        }

        int x1 = round(transformedDots[0].x);
        int x2 = round(transformedDots[1].x);
        int x3 = round(transformedDots[2].x);

        double z1 = transformedDots[0].z;
        double z2 = transformedDots[1].z;
        double z3 = transformedDots[2].z;

        int y1 = round(transformedDots[0].y);
        int y2 = round(transformedDots[1].y);
        int y3 = round(transformedDots[2].y);


#pragma omp parallel for
        for (int curY = (y1 < 0) ? 0 : y1;
             curY < ((y2 >= (int) ControlSystem::Buffer::height) ? (int) ControlSystem::Buffer::height - 1 : y2); curY++)
        {
            double aInc = 0;
            if (y1 != y2)
                aInc = (double)(curY - y1) / (y2 - y1);

            double bInc = 0;
            if (y1 != y3)
                bInc = (double)(curY - y1) / (y3 - y1);

            int xA = round(x1 + (x2 - x1) * aInc);
            int xB = round(x1 + (x3 - x1) * bInc);
            double zA = z1 + (z2 - z1) * aInc;
            double zB = z1 + (z3 - z1) * bInc;

            if (xA > xB)
            {
                std::swap(xA, xB);
                std::swap(zA, zB);
            }

            if (xA < 0)
                xA = 0;
            if (xB >= (int) ControlSystem::Buffer::width)
                xB = (int) ControlSystem::Buffer ::width - 1;

            NewDrawVisitor::interpolateRowIntoShadowMap(shadowMap, xA, xB, zA, zB, curY);
        }

#pragma omp parallel for
        for (int curY = (y2 < 0) ? 0 : y2;
             curY <= ((y3 >= (int) ControlSystem::Buffer::height) ? (int) ControlSystem::Buffer::height - 1 : y3); curY++)
        {
            double aInc = 0;
            if (y2 != y3)
                aInc = (double)(curY - y2) / (y3 - y2);

            double bInc = 0;
            if (y1 != y3)
                bInc = (double)(curY - y1) / (y3 - y1);

            int xA = round(x2 + (x3 - x2) * aInc);
            int xB = round(x1 + (x3 - x1) * bInc);
            double zA = z2 + (z3 - z2) * aInc;
            double zB = z1 + (z3 - z1) * bInc;

            if (xA > xB)
            {
                std::swap(xA, xB);
                std::swap(zA, zB);
            }

            if (xA < 0)
                xA = 0;
            if (xB >= (int) ControlSystem::Buffer::width)
                xB = (int) ControlSystem::Buffer ::width - 1;

            NewDrawVisitor::interpolateRowIntoShadowMap(shadowMap, xA, xB, zA, zB, curY);
        }
    }
    // file.close();
}


void NewDrawVisitor::zBufForModel(std::list<Facet> &facets, glm::mat4 transform, std::shared_ptr<Camera> &camera) 
{
    glm::mat4x4 model = transform;
    glm::mat4x4 projection = camera->get_perspective_matrix();
    glm::mat4x4 view = camera->get_view_matrix();
    glm::vec4 viewport(0.0f, 0.0f, ControlSystem::Buffer::width, ControlSystem::Buffer::height);
    glm::vec4 viewportshadow(0.0f, 0.0f, ControlSystem::Buffer::shadow_res, ControlSystem::Buffer::shadow_res);
    glm::mat4 proj = projection * view;

    float intensity = 0.0f;


    // std::ofstream file1("modeltransform.txt");
    // std::ofstream file("buffer.txt");
    // std::ofstream colorfile("color.txt");
    for (auto &facet : facets)
    {
        glm::vec3 p0 = facet.A;
        glm::vec3 p1 = facet.B;
        glm::vec3 p2 = facet.C;

        p0 = glm::vec3(glm::project(p0, model, proj, viewport));
        p1 = glm::vec3(glm::project(p1, model, proj, viewport));
        p2 = glm::vec3(glm::project(p2, model, proj, viewport));


        if (glm::isnan(p0.x) || glm::isnan(p0.y) || glm::isnan(p0.z) || glm::isnan(p1.x) || glm::isnan(p1.y) || glm::isnan(p1.z) || glm::isnan(p2.x) || glm::isnan(p2.y) || glm::isnan(p2.z))
        {
            continue;
        }
        if (p0.z < 1.0f || p1.z < 1.0f || p2.z < 1.0f)
        {
            continue;
        }
        std::array<glm::vec3, 3> transformedPoints = {
            p0, p1, p2
        };

        // file1 << "====================" << std::endl;
        // file1 << "x1: " << facet.A.x << " x2: " << facet.B.x << " x3: " << facet.C.x << std::endl;
        // file1 << "y1: " << facet.A.y << " y2: " << facet.B.y << " y3: " << facet.C.y << std::endl;
        // file1 << "z1: " << facet.A.z << " z2: " << facet.B.z << " z3: " << facet.C.z << std::endl;
        // file1 << ">------------------<" << std::endl;
        // file1 << "x1: " << transformedPoints[0].x << " x2: " << transformedPoints[1].x << " x3: " << transformedPoints[2].x << std::endl;
        // file1 << "y1: " << transformedPoints[0].y << " y2: " << transformedPoints[1].y << " y3: " << transformedPoints[2].y << std::endl;
        // file1 << "z1: " << transformedPoints[0].z << " z2: " << transformedPoints[1].z << " z3: " << transformedPoints[2].z << std::endl;
        // file1 << "====================" << std::endl;

        if (transformedPoints[0].y > transformedPoints[1].y)
            std::swap(transformedPoints[0], transformedPoints[1]);
        if (transformedPoints[0].y > transformedPoints[2].y)
            std::swap(transformedPoints[0], transformedPoints[2]);
        if (transformedPoints[1].y > transformedPoints[2].y)
            std::swap(transformedPoints[1], transformedPoints[2]);

        if (transformedPoints[2].y - transformedPoints[0].y <= 1)
        {
            continue;
        }

        int x1 = round(transformedPoints[0].x);
        int x2 = round(transformedPoints[1].x);
        int x3 = round(transformedPoints[2].x);

        double z1 = transformedPoints[0].z;
        double z2 = transformedPoints[1].z;
        double z3 = transformedPoints[2].z;

        int y1 = round(transformedPoints[0].y);
        int y2 = round(transformedPoints[1].y);
        int y3 = round(transformedPoints[2].y);

#pragma omp parallel for
        for (int curY = std::max(0, y1); curY < std::min((int)ControlSystem::Buffer::height, y2); curY++)
        {
            double aInc = (y1 != y2) ? (double)(curY - y1) / (y2 - y1) : 0;
            double bInc = (y1 != y3) ? (double)(curY - y1) / (y3 - y1) : 0;

            int xA = round(x1 + (x2 - x1) * aInc);
            int xB = round(x1 + (x3 - x1) * bInc);
            double zA = z1 + (z2 - z1) * aInc;
            double zB = z1 + (z3 - z1) * bInc;

            if (xA > xB) {
                std::swap(xA, xB);
                std::swap(zA, zB);
            }

            xA = std::max(0, xA);
            xB = std::min((int)ControlSystem::Buffer::width - 1, xB);

            for (int curX = xA; curX <= xB; curX++)
            {
                double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);


                if (curZ >= ControlSystem::Buffer::depth_buffer.at(curY).at(curX))
                {
                    short visible = 0;
                    glm::vec3 newCoordinates(curX, curY, curZ);

                    for (size_t i = 0; i < ControlSystem::SceneManager::get_lights().size() && !visible; i++)
                    {
                        auto &shadowMap = ControlSystem::SceneManager::get_lights().at(i)->shadow_buffer;

                        auto lightview = ControlSystem::SceneManager::get_lights().at(i)->get_view_matrix();
                        auto lightproj = ControlSystem::SceneManager::get_lights().at(i)->get_perspective_matrix();
                        glm::mat4 lightproject = lightproj * lightview;
                        auto newCoordinates2 = glm::unProject(newCoordinates, model, proj, viewport);
                        float distance = glm::length(newCoordinates2 - ControlSystem::SceneManager::get_lights().at(i)->get_center());

                        newCoordinates2 = glm::project(newCoordinates2, model, lightproject, viewportshadow);

                        intensity = ControlSystem::SceneManager::get_lights().at(i)->intensity / (distance + 0.0001f) * 1.75f;

                        int x = round(newCoordinates2.x);
                        int y = round(newCoordinates2.y);

                        if (x >= 0 && x < (int)shadowMap.size() && y >= 0 && y < (int)shadowMap[0].size())
                        {
                            // file << "diff[" << x << "][" << y << "] = " << std::fabs(shadowMap[x][y] - newCoordinates2.z) << std::endl;
                            if (std::fabs(shadowMap[x][y] - newCoordinates2.z) < 0.000075f)
                            {
                                visible = 1;
                                intensity /= shadowMap[x][y];
                            }
                        }
                        // file << "===============" << std::endl;

                    }
                    ControlSystem::Buffer::depth_buffer.at(curY).at(curX) = curZ;
                    // if (visible == 0 && SceneManager::get_lights().size() > 0)
                    if (visible == 0)
                    {
                        uint32_t color = facet.color;
                        int r = (color & 0xFF000000) >> 24;
                        int g = (color & 0x00FF0000) >> 16;
                        int b = (color & 0x0000FF00) >> 8;
                        int a = color & 0x000000FF;
                        r *= 0.2f;
                        g *= 0.2f;
                        b *= 0.2f;
                        a *= 0.2f;
                        color = (r << 24) | (g << 16) | (b << 8) | a;
                        // colorfile << "=======================\n";
                        // colorfile << "at (" << curX << ", " << curY << ") color1 (shaded): " << r << " " << g << " " << b << " " << a << std::endl;
                        ControlSystem::Buffer::frame_buffer.at(curY).at(curX) = color;
                    }
                    else
                    {
                        uint32_t color = facet.color;
                        int r = (color & 0xFF000000) >> 24;
                        int g = (color & 0x00FF0000) >> 16;
                        int b = (color & 0x0000FF00) >> 8;
                        int a = color & 0x000000FF;

                        r *= intensity;
                        g *= intensity;
                        b *= intensity;
                        a *= intensity;
                        color = (r << 24) | (g << 16) | (b << 8) | a;
                        // colorfile << "=======================\n";
                        // colorfile << "at (" << curX << ", " << curY << ") color1 (original): " << facet.color << std::endl;
                        ControlSystem::Buffer::frame_buffer.at(curY).at(curX) = color;
                    }
                }
            }
        }
#pragma omp parallel for
        for (int curY = (y2 < 0) ? 0 : y2;
             curY <= ((y3 >= (int) ControlSystem::Buffer::height) ? (int) ControlSystem::Buffer::height - 1 : y3); curY++)
        {
            double aInc = 0;
            if (y2 != y3)
                aInc = (double) (curY - y2) / (y3 - y2);

            double bInc = 0;
            if (y1 != y3)
                bInc = (double) (curY - y1) / (y3 - y1);

            int xA = round(x2 + (x3 - x2) * aInc);
            int xB = round(x1 + (x3 - x1) * bInc);
            double zA = z2 + (z3 - z2) * aInc;
            double zB = z1 + (z3 - z1) * bInc;

            if (xA > xB)
            {
                std::swap(xA, xB);
                std::swap(zA, zB);
            }

            if (xA < 0)
                xA = 0;
            if (xB >= (int) ControlSystem::Buffer::width)
                xB = (int) ControlSystem::Buffer::width - 1;

            for (int curX = xA; curX <= xB; curX++)
            {
                double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);

                if (curZ >= ControlSystem::Buffer::depth_buffer.at(curY).at(curX))
                {
                    short visible = 0;
                    glm::vec3 newCoordinates(curX, curY, curZ);

                    for (size_t i = 0; i < SceneManager::get_lights().size() && !visible; i++)
                    {
                        auto &shadowMap = SceneManager::get_lights().at(i)->shadow_buffer;

                        auto lightview = SceneManager::get_lights().at(i)->get_view_matrix();
                        auto lightproj = SceneManager::get_lights().at(i)->get_perspective_matrix();
                        glm::mat4 lightproject = lightproj * lightview;
                        auto newCoordinates2 = glm::unProject(newCoordinates, model, proj, viewport);
                        float distance = glm::length(newCoordinates2 - SceneManager::get_lights().at(i)->get_center());

                        newCoordinates2 = glm::project(newCoordinates2, model, lightproject, viewportshadow);

                        intensity = SceneManager::get_lights().at(i)->intensity / (distance + 0.0001f) * 1.75f;

                        int x = round(newCoordinates2.x);
                        int y = round(newCoordinates2.y);

                        if (x >= 0 && x < (int)shadowMap.size() && y >= 0 && y < (int)shadowMap[0].size())
                        {
                            // file << "diff[" << x << "][" << y << "] = " << std::fabs(shadowMap[x][y] - newCoordinates2.z) << std::endl;
                            if (std::fabs(shadowMap[x][y] - newCoordinates2.z) < 0.000075f)
                            {
                                visible = 1;
                                intensity /= shadowMap[x][y];
                            }
                        }
                        // file << "===============" << std::endl;

                    }
                    ControlSystem::Buffer::depth_buffer.at(curY).at(curX) = curZ;
                    // if (visible == 0 && SceneManager::get_lights().size() > 0)
                    if (visible == 0)
                    {
                        uint32_t color = facet.color;
                        int r = (color & 0xFF000000) >> 24;
                        int g = (color & 0x00FF0000) >> 16;
                        int b = (color & 0x0000FF00) >> 8;
                        int a = color & 0x000000FF;
                        r *= 0.2f;
                        g *= 0.2f;
                        b *= 0.2f;
                        a *= 0.2f;
                        color = (r << 24) | (g << 16) | (b << 8) | a;
                        // colorfile << "=======================\n";
                        // colorfile << "at (" << curX << ", " << curY << ") color1 (shaded): " << r << " " << g << " " << b << " " << a << std::endl;
                        ControlSystem::Buffer::frame_buffer.at(curY).at(curX) = color;
                    }
                    else
                    {
                        uint32_t color = facet.color;
                        int r = (color & 0xFF000000) >> 24;
                        int g = (color & 0x00FF0000) >> 16;
                        int b = (color & 0x0000FF00) >> 8;
                        int a = color & 0x000000FF;

                        r *= intensity;
                        g *= intensity;
                        b *= intensity;
                        a *= intensity;
                        color = (r << 24) | (g << 16) | (b << 8) | a;

                        // colorfile << "=======================\n";
                        // colorfile << "at (" << curX << ", " << curY << ") color1 (original): " << facet.color << std::endl;
                        ControlSystem::Buffer::frame_buffer.at(curY).at(curX) = color;
                    }
                }
            }
        }
    }
    // file.close();
    // file1.close();
    // colorfile.close();
}


#endif
