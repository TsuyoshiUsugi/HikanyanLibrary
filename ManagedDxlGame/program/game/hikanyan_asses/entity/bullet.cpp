#include "bullet.h"


void bullet::draw()
{
    DrawBoxEx(transform.position, transform.scale.x, transform.scale.y, false);
}

void bullet::gameStart()
{
}

void bullet::update(float delta_time)
{
    transform.position.y -= 500 * delta_time;
    if(transform.position.y <100)
    {
        setIsSurvival(false);
    }
}
void bullet::setPosition(const tnl::Vector3& position)
{
    transform.position = position;
}