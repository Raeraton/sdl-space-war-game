//
// Created by Aron on 2/25/2025.
//

#ifndef MENU_H
#define MENU_H

#include "display.h"


namespace menu {

    int new_menu( display::Screen& screen, bool* running, int num_of_menu_points, int box_width=100, int box_height=25, int gap=10, int fgap=50,
        const display::Color_rgba& background_color={0,0,0,255},
        const display::Color_rgba& textbox_color1={0,0,200,255},
        const display::Color_rgba& textbox_color2={0,0,255,255}
    );

    int main_menu(display::Screen& screen, bool* running); // 0: play   1:settings   2: exit

}


#endif //MENU_H
