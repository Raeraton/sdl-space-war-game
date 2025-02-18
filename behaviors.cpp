//
// Created by Aron on 2025. 02. 18..
//

#include "behaviors_n_animations.h"


namespace behaviors {

    void default_collision( game::engine::Object* self, game::engine::Object* other, bool is_collider ) {
        auto nect_vet = self->_velocity * ( self->get_mass() / other->get_mass() );

        if ( is_collider ) {
            other->_collision_behavior( other, self, false );
            other->_velocity += nect_vet;
        }else {
            other->_velocity = nect_vet;
        }

    }

}