#pragma once
#include "entity.h"
#include "../system/list.h"
#include "../system/singleton.h"

class entity_controller : public singleton<entity_controller>
{
private:
    void initialize();
    int num_enemies = 10;
public:
    void gameStart();
    void draw();
    void update(float delta_time);
    void bulletInstance(tnl::Vector3 position);
    void enemyInstance(tnl::Vector3 position);
    my_list<entity*> entityList;
};
