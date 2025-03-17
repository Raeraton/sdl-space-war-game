//
// Created by Aron on 2025. 02. 09..
//

#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include "keyboard.h"



namespace global_variables {

    void keyboard_init();
    inputs::Keyboard& get_keyboard();

    void set_deltatime( float );
    float get_deltatime();



#define NUM_OF_DATAS 14
    struct Global_data {
        int screen_width;
        int screen_height;

        float player_ship_nose_len;
        float player_ship_back_len;
        float player_ship_mass;
        float player_rotator_force;
        float player_engine_force;
        float player_health;

        float player_shoot_delay;
        float player_bullet_speed;
        float player_bullet_radius;
        float player_bullet_mass;
        int bullet_fragment_num;
        float projectile_lifetime;
    };

    Global_data& get_global_data();
    void set_global_data( const Global_data* );


}



#endif //GLOBAL_VARIABLES_H
