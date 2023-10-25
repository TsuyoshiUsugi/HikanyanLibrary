#pragma once
#include "entity.h"

class bullet : public entity
{
public:
    bullet()
    {
        transform.position = tnl::Vector3(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT * 0.8, 0);
        transform.rotation = tnl::Vector3(0, 0, 0);
        transform.scale = tnl::Vector3(20, 50, 1);
        _speed = 20.0f;
        setIsSurvival(true);
        collider.size = transform.scale;
        tag = "bullet";
    }

    void draw() override;
    void gameStart() override;
    void update(float delta_time) override;
    void setPosition(const tnl::Vector3& position);
protected:
    float _speed;
};
