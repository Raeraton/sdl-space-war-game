//
// Created by Aron on 2025. 02. 13..
//

#ifndef ENGINE_H
#define ENGINE_H

#include "display.h"
#include "game_math.h"

#include <vector>


namespace game::engine {

    class Phicics_engine;



    class Object {
        float _radius{};
        float _mass{};

    public:
        float _energy_of_last_collision = 0.0f;
        bool _is_dynamic{};
        Vector2 _position{};
        Vector2 _velocity{};
        float _direction{};
        float _angular_velocity{};
        float _numbers[16]{};   // numbers to use

        std::vector<display::Shape> (*_get_graphics)( const Object& self ){};   // no need to use lambda...
        void (*_update_behavior)( Object* );
        void (*_collision_behavior)( Object* self, Object* other, bool is_collider );  // is_collider true: ha ő vlt az 1. aki ütközöt
        void (*_death_behavior)( game::engine::Object*, game::engine::Phicics_engine* );

        Object() = default;
        Object( bool is_dynamic, float radius, float mass, Vector2 position, Vector2 velocity,
                float direction, float angular_velocity) :
                _is_dynamic(is_dynamic), _radius(radius), _mass(mass),
                _position(position), _velocity(velocity), _direction(direction), _angular_velocity(angular_velocity){}
        // picit csunya, de egyérelmű



        float get_radius() const { return _radius; }
        float get_mass() const { return _mass; }
        inline float get_kinetic_energy() const;


        void accelerate( const Vector2& acceleration );
        void rotate( float r );

        void update();

        void operator=(const game::engine::Object &other);
    };


    bool test_for_collision( const Object& obj1, const Object& obj2 );



    class Phicics_engine {
        std::vector<Object*> _objects{};
    public:
        Phicics_engine() = default;
        ~Phicics_engine();

        void update_objects();
        void display_objects( display::Screen& screen ) const;
        void delete_notexisting_object();

        void add_object( Object* object );
        void remove_object( int index );

    };


}



#endif //ENGINE_H
