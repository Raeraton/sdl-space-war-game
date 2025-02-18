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



    struct Global_data {
        int screen_width;
        int screen_height;
        float player_ship_nose_len;
        float player_ship_back_len;
        float player_shoot_delay;
        float player_hvp_speed;
        float player_hvp_radius;
        float player_hvp_mass;
        float player_ship_mass;
        float player_rotator_force;
        float player_engine_force;
        float player_health;
    };

    Global_data& get_global_data();
    void set_global_data( const Global_data& );


}



#endif //GLOBAL_VARIABLES_H
