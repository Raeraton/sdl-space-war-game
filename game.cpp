//
// Created by Aron on 2025. 02. 09..
//



#include "game.h"

#include "behaviors_n_animations.h"
#include "global_variables.h"


namespace game {


    Player::Player(const Controls &controls, const Vector2 &pos, engine::Phicics_engine& phicics_engine) : _object({
            false,
            global_variables::get_global_data().player_ship_nose_len, global_variables::get_global_data().player_ship_mass, pos, {0, 0}, 3.1415926535/*up dir*/, 0,
            animations::ship, behaviors::default_collision
        }) {
        _controls = controls;

        phicics_engine.add_object( &_object );
    }




    void Player::handle_input() {

        auto& keyboard = global_variables::get_keyboard();
        auto& gd = global_variables::get_global_data();

        if( keyboard.is_pressed( _controls.forward ) ) {
            _object.accelerate( polar_to_vector2( gd.player_engine_force, _object._direction) );
        }

        if ( keyboard.is_pressed( _controls.shoot ) ) {
            SDL_Log("puty");
        }

        if( keyboard.is_pressed( _controls.left ) ) {
            _object.rotate( -gd.player_rotator_force );
        }

        if( keyboard.is_pressed( _controls.right ) ) {
            _object.rotate( gd.player_rotator_force );
        }

    }



    std::vector<display::Shape> Player::get_player_specific_graphics() const {
        std::vector<display::Shape> out;

        auto& keyboard = global_variables::get_keyboard();
        auto& gd = global_variables::get_global_data();

        if( keyboard.is_pressed( _controls.forward ) ) {
            out.push_back( {
                ._type = 't',
                ._color = { 255, 255, 0, 255 },
                ._points = {
                    vector2_to_pixel_coord(_object._position + polar_to_vector2( gd.player_ship_back_len, _object._direction + 2.5f )),
                    vector2_to_pixel_coord(_object._position + polar_to_vector2( gd.player_ship_back_len, _object._direction - 2.5f )),
                    vector2_to_pixel_coord(_object._position + polar_to_vector2( -1.0f * gd.player_ship_nose_len, _object._direction ))
                }
            } );
        }

        return out;
    }


}
