//
// Created by Aron on 2025. 02. 18..
//

#ifndef BEHAVIORS_N_ANIMATIONS_H
#define BEHAVIORS_N_ANIMATIONS_H

#include "engine.h"

#include <vector>


namespace behaviors {

    void default_collision( game::engine::Object* self, game::engine::Object* other, bool is_collider );


}


namespace animations {

    std::vector<display::Shape> ship( const game::engine::Object& self );

    std::vector<display::Shape> bullet( const game::engine::Object& self );

}



#endif //BEHAVIORS_N_ANIMATIONS_H
