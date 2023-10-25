#include "enemy.h"


void enemy::gameStart()
{
};

void enemy::update(float delta_time)
{
    transform.position.y += 500 * delta_time;
    if (transform.position.y > DXE_WINDOW_HEIGHT * 0.2)
    {
        setIsSurvival(false);
    }
};

void enemy::draw()
{
    DrawBoxEx(transform.position, transform.scale.x, transform.scale.y, false);
};


void enemy::setPosition(const tnl::Vector3& position)
{
    transform.position = position;
}
