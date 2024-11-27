#ifndef __NEWDRAWVISITOR_H__
#define __NEWDRAWVISITOR_H__


#include "AbstractVisitor.h"
#include "Camera.h"
#include "Light.h"
#include "ModelType/Facet.h"
#include <memory>



class NewDrawVisitor
{
public:

    static void shadow_for_model(std::list<Facet>& facets,
                                 glm::mat4 transform,
                                 std::shared_ptr<Light>& light);

    static void zBufForModel(std::list<Facet>& facets,
                             glm::mat4 transform,
                             std::shared_ptr<Camera>& camera);


    static void interpolateRowIntoShadowMap(std::vector<std::vector<double>>& map, int xA, int xB, double zA, double zB, int curY)
    {
        for (int curX = xA; curX <= xB; curX++)
        {
            double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);
            if (curX >= (int) map.size() || curX < 0 || curY >= (int) map.at(0).size() || curY < 0)
                continue;

            if (curZ > map.at(curX).at(curY))
            {
                map.at(curX).at(curY) = curZ;
            }
        }
    }
};

class ShadowMapper : public AbstractVisitor
{
public:
    ShadowMapper() = delete;
    ShadowMapper(std::shared_ptr<Light>& light) : light(light) {} 
    ~ShadowMapper() = default;

    void visit(Model& obj) override
    {
        glm::mat4 back = this->transform;
        this->transform *= obj.transform;
        NewDrawVisitor::shadow_for_model(obj.model->get_surfaces(), this->transform, this->light);
        this->transform = back;
    }
    void visit(CompositeObject& obj) override
    {
        glm::mat4x4 back = this->transform;
        this->transform *= obj.transform;
        for (auto& element : obj)
        {
            element->accept(std::make_shared<ShadowMapper>(*this));
        }
        this->transform = back;
    }
    void visit(Light& obj) override
    {
        return;
    }
    void visit(Camera& obj) override
    {
        return;
    }

private:
    std::shared_ptr<Light>& light;
    glm::mat4x4 transform = glm::mat4x4(1.0f);
};

class ZBufMapper : public AbstractVisitor
{
public:
    ZBufMapper() = delete;
    ZBufMapper(std::shared_ptr<Camera>& camera) : camera(camera) {} 
    ~ZBufMapper() = default;

    void visit(Model& obj) override
    {
        glm::mat4 back = this->transform;
        this->transform *= obj.transform;
        NewDrawVisitor::zBufForModel(obj.model->get_surfaces(), this->transform, this->camera);
        this->transform = back;
    }
    void visit(CompositeObject& obj) override
    {
        glm::mat4x4 back = this->transform;
        this->transform *= obj.transform;
        for (auto& element : obj)
        {
            element->accept(std::make_shared<ZBufMapper>(*this));
        }
        this->transform = back;
    }
    void visit(Light& obj) override
    {
        return;
    }
    void visit(Camera& obj) override
    {
        return;
    }

private:
    std::shared_ptr<Camera>& camera;
    glm::mat4x4 transform = glm::mat4x4(1.0f);
};


#include "NewDrawVisitor.hpp"

#endif
