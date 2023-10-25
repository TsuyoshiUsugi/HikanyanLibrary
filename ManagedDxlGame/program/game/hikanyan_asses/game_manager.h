#pragma once
#include "system/singleton.h"

class game_manager : public singleton<game_manager>
{
private:

public:
    static void gameStart();
    static void gameMain( float delta_time );
    static void gameEnd();
};
