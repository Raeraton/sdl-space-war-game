//
// Created by Aron on 2025. 02. 13..
//

#ifndef ENGINE_H
#define ENGINE_H

#include "display.h"
#include "game_math.h"

#include <vector>


namespace game::engine {


    class Object {
        float _radius{};
        float _mass{};

    public:
        bool _is_existing{};
        const bool _is_dynamic{};
        Vector2 _position{};
        Vector2 _velocity{};
        float _direction{};
        float _angular_velocity{};

        std::vector<display::Shape> (*_get_graphics)( const Object& self ){};   // no need to use lambda...
        void (*_collision_behavior)( Object* self, Object* other, bool is_collider ){};  // is_collider true: ha ő vlt az 1. aki ütközött

        Object() = default;
        Object( bool is_dynamic, float radius, float mass, Vector2 position, Vector2 velocity,
                float direction, float angular_velocity,
                std::vector<display::Shape> (*get_graphics)( const Object& ),
                void (*collision_behavior)( Object*, Object*, bool )) :
                _is_dynamic(is_dynamic), _radius(radius), _mass(mass), _is_existing(true),
                _position(position), _velocity(velocity), _direction(direction), _angular_velocity(angular_velocity),
                _get_graphics(get_graphics), _collision_behavior(collision_behavior) {}
        // picit csunya, de egyérelmű



        float get_radius() const { return _radius; }
        float get_mass() const { return _mass; }


        void accelerate( const Vector2& acceleration );
        void rotate( float r );

        void update();

    };


    bool test_for_collision( const Object& obj1, const Object& obj2 );



    class Phicics_engine {
        std::vector<Object*> _objects{};
    public:
        Phicics_engine() = default;

        void update_objects();
        void handle_collisions();
        void display_objects( display::Screen& screen ) const;
        void delete_notexisting_object();

        void add_object( Object* object );
        void remove_object( int index );

    };


}



#endif //ENGINE_H
