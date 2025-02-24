//
// Created by Aron on 2025. 02. 09..
//

#ifndef GAME_H
#define GAME_H



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

    public:
        Player( const Controls& controls, const Vector2& pos, engine::Phicics_engine* phicics_engine );

        void handle_input();
        void shoot();

        std::vector<display::Shape> get_player_specific_graphics() const;
    };



}




#endif //GAME_H
