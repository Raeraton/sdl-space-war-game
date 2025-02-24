//
// Created by Aron on 2025. 02. 18..
//

#include "behaviors_n_animations.h"


namespace behaviors {

    void default_collision( game::engine::Object* self, game::engine::Object* other, bool is_collider ) {
        auto temp = self->_velocity;
        self->_velocity = other->_velocity * ( other->get_mass() / self->get_mass() );
        other->_velocity = temp * ( self->get_mass() / other->get_mass() );

    }

}