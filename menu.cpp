//
// Created by Aron on 2/25/2025.
//

#include "menu.h"
#include "global_variables.h"



namespace menu {

    int new_menu( display::Screen& screen, bool* running, int num_of_menu_points, int box_width, int box_height, int gap, int fgap,
        const display::Color_rgba& background_color,
        const display::Color_rgba& textbox_color1,
        const display::Color_rgba& textbox_color2
    ) {

        auto& gd = global_variables::get_global_data();
        auto& keyboard = global_variables::get_keyboard();
        keyboard.flush();

        int index = 0;
        int last_handled_key_pressed = 0;
        SDL_Event event;
        while( *running && !keyboard.is_pressed(SDLK_RETURN) ) {
            screen.update_size();
            int left_side = (gd.screen_width - box_width) / 2;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    *running = false;
                    break;
                }if( event.type == SDL_KEYDOWN  or  event.type == SDL_KEYUP ) {
                    keyboard.update( event );
                }
            }

            int key_pressed = keyboard.last_pressed();
            if( key_pressed == SDLK_UP  &&  key_pressed != last_handled_key_pressed  ) {
                index = (index) ? index-1 : num_of_menu_points-1;
            }if( key_pressed == SDLK_DOWN  &&  key_pressed != last_handled_key_pressed ) {
                index = (index < num_of_menu_points-1) ? index+1 : 0;
            }
            last_handled_key_pressed = key_pressed;


            screen.fill( background_color );

            std::vector<display::Shape> shapes;
            shapes.reserve( num_of_menu_points );
            for( int i = 0; i < num_of_menu_points; i++ ) {
                shapes.push_back({
                    ._type = 'r',
                    ._color = index==i? textbox_color1 : textbox_color2,
                    ._points = {
                        { left_side, fgap+i*(gap+box_height) },
                        { box_width, box_height },
                    }
                });
            }
            screen.draw_shapes(shapes);

            screen.display();
        }

        return index;

    }


    int main_menu(display::Screen& screen, bool* running) {
        auto& gd = global_variables::get_global_data();

        return new_menu( screen, running, 3, gd.screen_width/3*2, 50, 50, 150,
            {5,7,11,255}, {150,150,150,255}, {37, 41, 43,255} ); // play, settings, exit
    }





}
