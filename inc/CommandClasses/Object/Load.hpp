#include "Load.h"

#include "Builders/SurfaceBuilder.h"


Actions::Object::LoadTXTUncolored::LoadTXTUncolored(std::shared_ptr<AbstractObject>& obj, const std::string& filename)
    : obj(obj), filename(filename)
{
    this->method = &ControlSystem::LoadManager::load_from_file<SurfaceBuilder>;
}

void Actions::Object::LoadTXTUncolored::Execute()
{
    this->obj = (*method)(this->filename);
}



