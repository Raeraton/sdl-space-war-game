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
            global_variables::get_global_data().player_ship_nose_len, global_variables::get_global_data().player_ship_mass,
            pos, {0, 0}, 1.57f/*up dir*/, 0.0f
        }) {
        _health = global_variables::get_global_data().player_health;

        _object._update_behavior = behaviors::default_movement;
        _object._collision_behavior = behaviors::default_collision;
        _object._death_behavior = behaviors::default_death;
        _object._get_graphics = animations::ship;

        _controls = controls;

        _engine = phicics_engine;
        phicics_engine->add_object( &_object );
    }



    float Player::get_health() const {
        return _health;
    }
    void Player::give_damage(){
        _health -= _object._energy_of_last_collision;
        if( _object._energy_of_last_collision != 0.0f )  SDL_Log("dam: %f" ,_object._energy_of_last_collision);
        _object._energy_of_last_collision = 0.0f;
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

        if( std::chrono::duration<float>( std::chrono::system_clock::now() - _last_time_shot ).count() < gd.player_shoot_delay  )
            return;
        _last_time_shot = std::chrono::system_clock::now();


        auto spawn_pos = _object._position + polar_to_vector2( gd.player_ship_nose_len+gd.player_bullet_radius+1.0f, _object._direction );

        auto* new_bullet = new game::engine::Object( true, gd.player_bullet_radius, gd.player_bullet_mass,
            spawn_pos, _object._velocity+polar_to_vector2(gd.player_bullet_speed, _object._direction), _object._direction, 0.0f);

        new_bullet->_update_behavior = behaviors::bullet_movement;
        new_bullet->_collision_behavior = behaviors::bullet_collision;
        new_bullet->_death_behavior = behaviors::bullet_death;
        new_bullet->_get_graphics = animations::bullet;

        _engine->add_object( new_bullet );

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
