#include <SDL.h>
#include <chrono>

#include "display.h"
#include "keyboard.h"
#include "game.h"
#include "global_variables.h"




int main(int argc, char* args []) {
    SDL_Init(SDL_INIT_VIDEO);


    global_variables::set_global_data({
        .screen_width = 1280,
        .screen_height = 720,
        .player_ship_nose_len = 15,
        .player_ship_back_len = 5,
        .player_shoot_delay = 2,
        .player_hvp_speed = 100,
        .player_hvp_radius = 3,
        .player_hvp_mass = 1,
        .player_ship_mass = 5,
        .player_rotator_force = 3.141592653589793,
        .player_engine_force = 50,
        .player_health = 10
    });

    auto& gd = global_variables::get_global_data();


    global_variables::keyboard_init();
    auto& keyboard = global_variables::get_keyboard();


    display::Screen screen( "test win", gd.screen_width, gd.screen_height  );
    if( not screen.is_open() )
        return -1;


    game::engine::Phicics_engine engine{};

    game::Player player1( { 'w', 's', 'a', 'd' }, {200, 200}, &engine );
    game::Player player2( { 'i', 'k', 'j', 'l' }, {300, 300}, &engine );


    // main loop
    auto time_point = std::chrono::high_resolution_clock::now();
    SDL_Event event;
    bool running = true;
    while (running) {
        {
            auto new_time = std::chrono::high_resolution_clock::now();
            global_variables::set_deltatime( std::chrono::duration<float>(new_time - time_point).count() );
            time_point = new_time;
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }if( event.type == SDL_KEYDOWN  or  event.type == SDL_KEYUP ) {
                keyboard.update( event );
            }
        }

        player1.handle_input();
        player2.handle_input();


        engine.delete_notexisting_object();
        engine.update_objects();


        screen.fill( display::Color_rgba{50, 51, 53, 255} );
        engine.display_objects( screen );

        screen.draw_shapes(  player1.get_player_specific_graphics()  );
        screen.draw_shapes(  player2.get_player_specific_graphics()  );

        screen.display();

    }



    return 0;

}

