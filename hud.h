//
// Created by Aron on 3/5/2025.
//

#ifndef HUD_H
#define HUD_H


#include "display.h"
#include "game.h"


namespace game::hud {

    /*
     * displays the players hp, and other stuffs
     */
    std::vector<display::Shape> get_hud( const game::Player&, const game::Player& );

}



#endif //HUD_H
