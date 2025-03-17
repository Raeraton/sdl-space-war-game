//
// Created by Aron on 3/5/2025.
//

#include "hud.h"
#include "global_variables.h"




namespace game::hud {

    std::vector<display::Shape> get_hud( const game::Player& player1, const game::Player& player2 ) {
        auto& gd = global_variables::get_global_data();
        std::vector<display::Shape> outp;
        outp.reserve(2);

        float bar_wid = gd.screen_width / 5 * 2;   // 40% of screen width
        constexpr int bar_hei = 15;

        outp.push_back( {
            ._type = 'r',
            ._color = { 0, 0, 0xff, 0xff },
            ._points = {
                { gd.screen_width/20, 5 },
                { static_cast<int>(bar_wid*player1.get_health()/gd.player_health), bar_hei}
            }
        } );

        outp.push_back( {
            ._type = 'r',
            ._color = { 0xff, 0, 0, 0xff },
            ._points = {
                { gd.screen_width/20*11, 5 },
                { static_cast<int>(bar_wid*player2.get_health()/gd.player_health), bar_hei}
            }
        } );

        return outp;
    }

}