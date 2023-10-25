#pragma once
#include "entity.h"

class player:public entity
{
public:
    player()
    {
        transform.position = tnl::Vector3(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT * 0.8, 0);
        transform.rotation = tnl::Vector3(0, 0, 0);
        transform.scale = tnl::Vector3(50, 100, 1);
        _speed =10.0f;
        setIsSurvival(true);
        collider.size = transform.scale;
    }
    void draw() override;
    void gameStart() override;
    void update(float delta_time) override;
    void OnTriggerEnter2D(entity* other) override;
protected:
    float _speed;
private:
    
};
