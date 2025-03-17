//
// Created by Aron on 2/25/2025.
//


#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "settings.h"
#include "global_variables.h"

static void save_settings() {
    std::ofstream file("settings.txt");
    if( !file.is_open() ) {
        throw std::runtime_error("settings.txt could not be opened to update");
    }

    auto gd = global_variables::get_global_data();

    constexpr int space = 32;

    file    << gd.screen_width             << std::setw(space) << " screen_width\n";
    file    << gd.screen_height            << std::setw(space) << " screen_height\n";
    file    << gd.player_ship_nose_len     << std::setw(space) << " player_ship_nose_len\n";
    file    << gd.player_ship_back_len     << std::setw(space) << " player_ship_back_len\n";
    file    << gd.player_ship_mass         << std::setw(space) << " player_ship_mass\n";
    file    << gd.player_rotator_force     << std::setw(space) << " player_rotator_force\n";
    file    << gd.player_engine_force      << std::setw(space) << " player_engine_force\n";
    file    << gd.player_health            << std::setw(space) << " player_health\n";
    file    << gd.player_shoot_delay       << std::setw(space) << " player_shoot_delay\n";
    file    << gd.player_bullet_speed      << std::setw(space) << " player_bullet_speed\n";
    file    << gd.player_bullet_radius     << std::setw(space) << " player_bullet_radius\n";
    file    << gd.player_bullet_mass       << std::setw(space) << " player_bullet_mass\n";
    file    << gd.bullet_fragment_num       << std::setw(space) << " player_bullet_fragment_num\n";
    file    << gd.projectile_lifetime       << std::setw(space) << " player_bullet_lifetime\n";

    file.close();
}

static global_variables::Global_data* read_settings_from_file() {
    auto gd = new global_variables::Global_data{};


    std::ifstream file("settings.txt");
    if (file.is_open()) {
        std::stringstream liness[NUM_OF_DATAS];
        for( int i=0; i<NUM_OF_DATAS; i++ ) {
            std::string line;
            std::getline(file, line);
            liness[i] = std::stringstream(line);
        }

        liness[0] >> gd->screen_width;
        liness[1] >> gd->screen_height;

        liness[2] >> gd->player_ship_nose_len;
        liness[3] >> gd->player_ship_back_len;
        liness[4] >> gd->player_ship_mass;
        liness[5] >> gd->player_rotator_force;
        liness[6] >> gd->player_engine_force;
        liness[7] >> gd->player_health;

        liness[8] >> gd->player_shoot_delay;
        liness[9] >> gd->player_bullet_speed;
        liness[10] >> gd->player_bullet_radius;
        liness[11] >> gd->player_bullet_mass;
        liness[12] >> gd->bullet_fragment_num;
        liness[13] >> gd->projectile_lifetime;
        file.close();
    }else{
        gd->screen_width = 1280;
        gd->screen_height = 720;

        gd->player_ship_nose_len = 15;
        gd->player_ship_back_len = 10;
        gd->player_ship_mass = 1;
        gd->player_rotator_force = 5;
        gd->player_engine_force = 100;
        gd->player_health = 100000;

        gd->player_shoot_delay = 0.33;
        gd->player_bullet_speed = 350;
        gd->player_bullet_radius = 3;
        gd->player_bullet_mass = 0.1;
        gd->bullet_fragment_num = 3;
        gd-> projectile_lifetime = 2.0;
    }


    return gd;
}

namespace settings {

    void import_settings() {
        auto gd = read_settings_from_file();
        global_variables::set_global_data( gd );
        delete gd;
    }

    void export_settings() {
        save_settings();
    }


}