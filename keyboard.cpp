//
// Created by Aron on 2025. 02. 09..
//

#include "keyboard.h"




inputs::Keyboard::Keyboard() {
    _keys = std::map<int, bool>();
    _last_pressed = 0;
    _last_released = 0;
}

bool inputs::Keyboard::is_pressed( int key ){
    return (_keys.count(key)>0) ? _keys[key] : false;
}

int inputs::Keyboard::last_pressed() const {
    return _last_pressed;
}
int inputs::Keyboard::last_released() const {
    return _last_released;
}



void inputs::Keyboard::update( SDL_Event& event ) {

    if( event.type == SDL_KEYDOWN ) {
        _keys[event.key.keysym.sym] = true;
        _last_pressed = event.key.keysym.sym;
    }else if(event.type == SDL_KEYUP) {
        _keys[event.key.keysym.sym] = false;
        _last_released = event.key.keysym.sym;
    }

}