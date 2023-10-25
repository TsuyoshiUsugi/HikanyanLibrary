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
    DrawStringEx(50, 50, -1, "ねこ");
    DrawStringEx(DXE_WINDOW_WIDTH / 2 - 80, DXE_WINDOW_HEIGHT * 0.2, -1, "シューティングゲーム");


    entity_controller::getInstance()->update(delta_time);
    entity_controller::getInstance()->draw();
}

void game_manager::gameEnd()
{
}
