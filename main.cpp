#include <SDL.h>
#include <chrono>

#include "display.h"
#include "keyboard.h"
#include "game.h"
#include "global_variables.h"
#include "settings.h"
#include "menu.h"
#include "hud.h"


int game_loop( display::Screen& screen, bool* running );   // -1:error 0: idk  1: 1st player win


int main(int argc, char* args []) {
    SDL_Init(SDL_INIT_VIDEO);

    settings::import_settings();
    auto& global_data = global_variables::get_global_data();

    global_variables::keyboard_init();

    display::Screen screen( "test win", global_data.screen_width, global_data.screen_height  );
    if( not screen.is_open() )
        return -1;




    bool running = true;
    while( running ) {
        int choise = menu::main_menu( screen, &running );
        switch( choise ) {
            case 0:
                game_loop( screen, &running );
                break;
            case 1:
                settings::import_settings();
                settings::export_settings();
                SDL_Log( "Settings menu isn't implemented" );
                SDL_Delay(100);
                break;
            case 2:
                running = false;
                break;
            default:
                break;
        }

    }


    return 0;

}




int game_loop( display::Screen& screen, bool* running ) {
    auto& keyboard = global_variables::get_keyboard();
    auto& gd = global_variables::get_global_data();

    game::engine::Phicics_engine engine{};

    game::Player player1( { 'w', 's', 'a', 'd' },
        { static_cast<float>(gd.screen_width/5), static_cast<float>(gd.screen_height/2) }, &engine );
    game::Player player2( { SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT },
        { static_cast<float>(gd.screen_width/5*4), static_cast<float>(gd.screen_height/2) }, &engine );


    // main loop
    auto time_point = std::chrono::high_resolution_clock::now();
    SDL_Event event;
    bool game_running = true;
    while (*running  &&  game_running ) {
        screen.update_size();
        {
            auto new_time = std::chrono::high_resolution_clock::now();
            global_variables::set_deltatime( std::chrono::duration<float>(new_time - time_point).count() );
            time_point = new_time;
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                *running = false;
                break;
            }if( event.type == SDL_KEYDOWN  or  event.type == SDL_KEYUP ) {
                keyboard.update( event );
            }
        }


        player1.handle_input();
        player2.handle_input();

        engine.update_objects();

        player1.give_damage();
        player2.give_damage();
        if( player1.get_health() <= 0.0f  or  player2.get_health() <= 0.0f ) {
            game_running = false;
        }


        screen.fill( display::Color_rgba{1, 5, 10, 255} );

        screen.draw_shapes( game::hud::get_hud(player1, player2) );
        engine.display_objects( screen );
        screen.draw_shapes(  player1.get_player_specific_graphics()  );
        screen.draw_shapes(  player2.get_player_specific_graphics()  );

        screen.display();


        if( keyboard.is_pressed(SDLK_ESCAPE) )
            game_running = false;

    }

    return 0;

}
