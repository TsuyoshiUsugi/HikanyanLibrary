#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class transform
{
public:

    tnl::Vector3 position{0, 0, 0};
    tnl::Vector3 rotation{0, 0, 0};
    tnl::Vector3 scale{1, 1, 1};
    
    transform()
    {
    }

    tnl::Vector3 getPosition()
    {
        tnl::Vector3 ret;
        get_position_Injected(ret);
        return ret;
    }

    void setPosition(const tnl::Vector3& value)
    {
        set_position_Injected(value);
    }

public:
    void get_position_Injected(tnl::Vector3& ret);
    void set_position_Injected(const tnl::Vector3& value);
};
