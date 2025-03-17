//
// Created by Aron on 2025. 02. 09..
//

#ifndef GAME_H
#define GAME_H



#include <chrono>

#include "display.h"
#include "engine.h"
#include "game_math.h"



namespace game {


    struct Controls {
        int forward, shoot, left, right;
    };

    class Player{
        Controls _controls{};
        engine::Object _object{};
        engine::Phicics_engine* _engine;
        float _health{};
        std::chrono::system_clock::time_point _last_time_shot{};

    public:
        Player( const Controls& controls, const Vector2& pos, engine::Phicics_engine* phicics_engine );

        float get_health() const;
        void give_damage();

        void handle_input();
        void shoot();

        std::vector<display::Shape> get_player_specific_graphics() const;
    };



}




#endif //GAME_H
