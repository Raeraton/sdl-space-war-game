//
// Created by Aron on 2025. 02. 18..
//

#include "behaviors_n_animations.h"
#include "global_variables.h"

namespace animations {

    std::vector<display::Shape> ship( const game::engine::Object& self ) {
        std::vector<display::Shape> graphics;

        const auto& global_data = global_variables::get_global_data();

        graphics.push_back( (display::Shape) {
            ._type = 't',
            ._color = { 0xff, 0xff, 0xff, 0xff },
            ._points = {
                game::vector2_to_pixel_coord(  self._position+game::polar_to_vector2( global_data.player_ship_nose_len, self._direction ) ),
                game::vector2_to_pixel_coord( self._position+game::polar_to_vector2( global_data.player_ship_back_len, self._direction+2.0943951024f ) ),
                game::vector2_to_pixel_coord( self._position+game::polar_to_vector2( global_data.player_ship_back_len, self._direction+4.1887902048f ) )
            }
        } );

        return graphics;

    }


    std::vector<display::Shape> bullet( const game::engine::Object& self ) {
        std::vector<display::Shape> graphics;

        const auto& global_data = global_variables::get_global_data();

        graphics.push_back( (display::Shape) {
            ._type = 't',
            ._color = { 0xff, 0xff, 0xff, 0xff },
            ._points = {
                game::vector2_to_pixel_coord(  self._position+game::polar_to_vector2( global_data.player_hvp_radius, self._direction ) ),
                game::vector2_to_pixel_coord( self._position+game::polar_to_vector2( global_data.player_hvp_radius, self._direction+2.0943951024f ) ),
                game::vector2_to_pixel_coord( self._position+game::polar_to_vector2( global_data.player_hvp_radius, self._direction+4.1887902048f ) )
            }
        } );


        return graphics;
    }

}
