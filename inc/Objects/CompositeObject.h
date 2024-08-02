#ifndef __COMPOSITE_OBJECT_H__
#define __COMPOSITE_OBJECT_H__

#include "AbstractObject.h"

class CompositeObject : public AbstractObject
{
public:
    using iterator = Iterator;
    using value_type = AbstractObject;
    using iterator_rag = std::random_access_iterator_tag;
    using pointer = std::shared_ptr<AbstractObject>;
    using reference = AbstractObject&;

    CompositeObject() = default;
    explicit CompositeObject(std::shared_ptr<AbstractObject>& object);
    explicit CompositeObject(std::vector<std::shared_ptr<AbstractObject>>& vector);

    bool IsDrawable() override;
    bool IsComposite() override;

    bool add(const std::shared_ptr<AbstractObject>& obj) override;
    bool remove(const Iterator& iterator) override;

    void accept(std::shared_ptr<AbstractVisitor> visitor) override;

    // std::vector<std::shared_ptr<AbstractObject>>& get();

    Iterator begin() override;
    Iterator end() override;

private:
    std::vector<std::shared_ptr<AbstractObject>> elements;
};

#include "CompositeObject.hpp"

#endif