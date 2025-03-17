//
// Created by Aron on 2025. 02. 09..
//

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <map>
#include <SDL_events.h>


namespace inputs {

    class Keyboard {
        std::map< int, bool > _keys;
        int _last_pressed;
        int _last_released;

    public:
        Keyboard();

        bool is_pressed( int );
        int last_pressed() const;
        int last_released() const;
        void flush();

        void update(const SDL_Event& event );
    };

}


#endif //KEYBOARD_H
