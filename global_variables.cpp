//
// Created by Aron on 2025. 02. 10..
//



#include "global_variables.h"


inputs::Keyboard GLOBAL_KEYBOARD;
float DELTATIME;
global_variables::Global_data GLOBAL_DATA;








global_variables::Global_data& global_variables::get_global_data() {
    return GLOBAL_DATA;
}
void global_variables::set_global_data( const global_variables::Global_data& gd ) {
    GLOBAL_DATA = gd;
}







void global_variables::keyboard_init() {
    GLOBAL_KEYBOARD = inputs::Keyboard();
}
inputs::Keyboard& global_variables::get_keyboard() {
    return GLOBAL_KEYBOARD;
}






void global_variables::set_deltatime( float input ) {
    DELTATIME = input;
}
float global_variables::get_deltatime() {
    return DELTATIME;
}