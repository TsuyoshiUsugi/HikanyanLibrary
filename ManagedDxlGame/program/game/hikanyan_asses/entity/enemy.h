#pragma once
#include "entity.h"

class enemy:public entity
{
public:
    enemy(){
        transform.position = tnl::Vector3(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT * 0.2, 0);
        transform.rotation = tnl::Vector3(0, 0, 0);
        transform.scale = tnl::Vector3(100, 100, 1);
        setIsSurvival(true);
        collider.size = transform.scale;
        tag = "enemy";
    }
    void draw() override;
    void gameStart() override;
    void update(float delta_time) override;
    void setPosition(const tnl::Vector3& position);
};
