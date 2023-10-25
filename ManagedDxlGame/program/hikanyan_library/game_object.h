#pragma once
#include "object.h"
#include "../dxlib_ext/dxlib_ext.h"


class Component;

class game_object : public object
{
public:
    class transform
    {
    public:
        tnl::Vector3 position{0, 0, 0};
        tnl::Vector3 rotation{0, 0, 0};
        tnl::Vector3 scale{1, 1, 1};
    };

    std::string tag() const
    {
        return tagValue;
    }

    void setTag(const std::string& value)
    {
        tagValue = value;
    }

    void addComponent(Component* component);
    void removeComponent(Component* component);

protected:
    std::vector<Component*> components; //コンポーネントの配列
    std::string tagValue;
};
