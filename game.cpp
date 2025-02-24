//
// Created by Aron on 2025. 02. 09..
//



#include "game.h"
#include "behaviors_n_animations.h"
#include "global_variables.h"

#include <chrono>

namespace game {


    Player::Player(const Controls &controls, const Vector2 &pos, engine::Phicics_engine* phicics_engine) : _object({
            false,
            global_variables::get_global_data().player_ship_nose_len, global_variables::get_global_data().player_ship_mass, pos, {0, 0}, 3.1415926535/*up dir*/, 0,
            animations::ship, behaviors::default_collision
        }) {
        _controls = controls;

        _engine = phicics_engine;
        phicics_engine->add_object( &_object );
    }




    void Player::handle_input() {

        auto& keyboard = global_variables::get_keyboard();
        auto& gd = global_variables::get_global_data();

        if( keyboard.is_pressed( _controls.forward ) ) {
            _object.accelerate( polar_to_vector2( gd.player_engine_force, _object._direction) );
        }

        if ( keyboard.is_pressed( _controls.shoot ) ) {
            shoot();
        }

        if( keyboard.is_pressed( _controls.left ) ) {
            _object.rotate( -gd.player_rotator_force );
        }

        if( keyboard.is_pressed( _controls.right ) ) {
            _object.rotate( gd.player_rotator_force );
        }

    }

    void Player::shoot() {
        auto& gd = global_variables::get_global_data();

        static auto last_tp = std::chrono::system_clock::now();
        if( std::chrono::duration<float>( std::chrono::system_clock::now() - last_tp ).count() < gd.player_shoot_delay  )
            return;
        last_tp = std::chrono::system_clock::now();


        auto spawn_pos = _object._position + polar_to_vector2( gd.player_ship_nose_len*1.5 , _object._direction );

        auto* nem_bullet = new game::engine::Object( true, gd.player_hvp_radius, gd.player_hvp_mass,
            spawn_pos, _object._velocity+polar_to_vector2(gd.player_hvp_speed, _object._direction), _object._direction, 0.0f,
            animations::bullet, behaviors::default_collision );

        _engine->add_object( nem_bullet );

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
