//
// Created by Aron on 2025. 02. 18..
//

#include "behaviors_n_animations.h"
#include "global_variables.h"


#define minfragrad 2
static void summon_bullet_fragments(game::engine::Object* self, game::engine::Phicics_engine* phicics_engine) {
    auto& gd = global_variables::get_global_data();

    float fragrad = self->get_radius()/gd.bullet_fragment_num;
    if (fragrad < minfragrad) fragrad = minfragrad;

    float dir_r = 6.28318530718f / static_cast<float>(gd.bullet_fragment_num);
    float angle = self->_direction;
    for( int i=0;  i<gd.bullet_fragment_num;  i++ ) {
        auto frag = new game::engine::Object;

        *frag = game::engine::Object( true,
            fragrad, self->get_mass()/gd.bullet_fragment_num,
            self->_position + game::polar_to_vector2( self->get_radius()*1.1f+self->get_radius()/gd.bullet_fragment_num, angle ),
            self->_velocity + game::polar_to_vector2( game::dist(self->_velocity, {0,0})*1.1f, angle ),
            angle, 0.0f );

        frag->_update_behavior = behaviors::bullet_movement;
        frag->_collision_behavior = behaviors::bullet_collision;
        frag->_death_behavior = behaviors::default_death;
        frag->_get_graphics = animations::bullet;

        SDL_Log("Frag: %p", frag);
        phicics_engine->add_object(frag);

        angle += dir_r;
    }


}



namespace behaviors {

    void default_movement( game::engine::Object* self ) {
        const float delta_time = global_variables::get_deltatime();
        const auto& gd = global_variables::get_global_data();
        self->_position += self->_velocity * delta_time;
        self->_direction += self->_angular_velocity * delta_time;

        if( self->_position.x < 0 ) self->_position.x = static_cast<float>(gd.screen_width);
        if( self->_position.y < 0 ) self->_position.y = static_cast<float>(gd.screen_height);
        if( self->_position.x > static_cast<float>(gd.screen_width) ) self->_position.x = 0.0f;
        if( self->_position.y > static_cast<float>(gd.screen_height) ) self->_position.y = 0.0f;

    }

    void default_collision( game::engine::Object* self, game::engine::Object* other, bool _is_collider ) {
        auto temp = self->_velocity;
        self->_position += self->_velocity * -1.0f * global_variables::get_deltatime();
        self->_velocity = other->_velocity * ( other->get_mass() / self->get_mass() );
        other->_velocity = temp * ( self->get_mass() / other->get_mass() );
    }

    void default_death( game::engine::Object* self, game::engine::Phicics_engine* phicics_engine ) {
        return;
    }

    void bullet_movement( game::engine::Object* self ) {
        float delta_time = global_variables::get_deltatime();
        auto& gd = global_variables::get_global_data();

        self->_position += self->_velocity * delta_time;
        self->_direction += self->_angular_velocity * delta_time;

        if(
            self->_position.x < 0 || self->_position.y < 0 ||
            self->_position.x > gd.screen_width || self->_position.y > gd.screen_height
        ) {
            self->_energy_of_last_collision = 12345678910.10987654321f;   // special case, for leaving the map
        }


        if( self->_numbers[0] > gd.projectile_lifetime )
            self->_energy_of_last_collision = 1.0f;
        self->_numbers[0] += delta_time;

    }

    void bullet_collision( game::engine::Object* self, game::engine::Object* other, bool _is_collider ) {
        SDL_Log("Bullet colided");

        other->_velocity += self->_velocity * ( self->get_mass() / other->get_mass() );

        other->_energy_of_last_collision = game::dist_pow2( other->_velocity, self->_velocity ) * self->get_mass();
        self->_energy_of_last_collision = 1.0f;
    }

    void bullet_death( game::engine::Object* self, game::engine::Phicics_engine* phicics_engine ) {
        if( self->_energy_of_last_collision == 12345678910.10987654321f )
            return;

        summon_bullet_fragments( self, phicics_engine );
    }

}