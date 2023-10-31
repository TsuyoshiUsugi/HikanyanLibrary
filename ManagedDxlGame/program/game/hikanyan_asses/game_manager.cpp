#include "game_manager.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "entity/entity_controller.h"
#include "entity/player.h"

void game_manager::gameStart()
{
    entity_controller::getInstance()->gameStart();
}

void game_manager::gameMain(float delta_time)
{
    entity_controller::getInstance()->update(delta_time);
    entity_controller::getInstance()->draw();
}

void game_manager::gameEnd()
{
}
