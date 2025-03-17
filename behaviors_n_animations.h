//
// Created by Aron on 2025. 02. 18..
//

#ifndef BEHAVIORS_N_ANIMATIONS_H
#define BEHAVIORS_N_ANIMATIONS_H

#include "engine.h"

#include <vector>


namespace behaviors {

    void default_movement( game::engine::Object* self );
    void default_collision( game::engine::Object* self, game::engine::Object* other, bool is_collider );
    void default_death( game::engine::Object* self, game::engine::Phicics_engine* phicics_engine );

    void bullet_movement( game::engine::Object* self );
    void bullet_collision( game::engine::Object* self, game::engine::Object* other, bool is_collider );
    void bullet_death( game::engine::Object* self, game::engine::Phicics_engine* phicics_engine );

}


namespace animations {

    std::vector<display::Shape> ship( const game::engine::Object& self );

    std::vector<display::Shape> bullet( const game::engine::Object& self );

}



#endif //BEHAVIORS_N_ANIMATIONS_H
