#include "engine.h"

#include <bits/streambuf_iterator.h>

#include "global_variables.h"



void game::engine::Object::operator=( const game::engine::Object& other ) {
    _mass = other._mass;
    _radius = other._radius;

    _energy_of_last_collision = other._energy_of_last_collision;
    _is_dynamic = other._is_dynamic;
    _position = other._position;
    _velocity = other._velocity;
    _direction = other._direction;
    _angular_velocity = other._angular_velocity;

    _get_graphics = other._get_graphics;
    _update_behavior = other._update_behavior;
    _collision_behavior = other._collision_behavior;
    _death_behavior = other._death_behavior;
}


namespace game::engine {


    void Object::accelerate( const Vector2& acceleration ) {
        _velocity += acceleration * global_variables::get_deltatime();
    }

    void Object::rotate( float r ) {
        _angular_velocity += r * global_variables::get_deltatime();
    }

    void Object::update() {
        _update_behavior(this);
    }



    bool test_for_collision( const Object& obj1, const Object& obj2 ) {
        // TODO optimise sqrt
        float max_radius = obj1.get_radius() + obj2.get_radius();

        if( max_radius > dist( obj1._position, obj2._position ) )
            return true;
        return false;
    }






    Phicics_engine::~Phicics_engine() {
        for( int i = 0; i < _objects.size(); ++i ) {
            remove_object(i);
        }
    }

    void Phicics_engine::update_objects() {
        delete_notexisting_object();

        for(auto & _object : _objects) {
            _object->update();
        }

        for(int i=0;  i<_objects.size();  i++) {

            if( game::dist_pow2( {0,0}, _objects[i]->_velocity ) == 0 ) {
                continue;
            }

            for(int j=0;  j<_objects.size();  j++) {
                if( j == i ) continue;
                if(  test_for_collision( *_objects[i], *_objects[j] )  ) {
                    _objects[i]->_collision_behavior( _objects[i], _objects[j], true );
                    break;    // breaks out the inner for loop....
                }
            }

        }


    }


    void Phicics_engine::display_objects( display::Screen& screen ) const {

        for(auto& object : _objects) {
            screen.draw_shapes(
                object->_get_graphics( *object )
            );
        }

    }
    void Phicics_engine::delete_notexisting_object() {
        for( int i=0;  i<_objects.size();  i++ ) {
            if( _objects[i]->_energy_of_last_collision > 0.0f  ) {
                remove_object( i );
            }
        }
    }


    void Phicics_engine::add_object( Object* object ) {
        SDL_Log("adding object index %p", _objects );
        _objects.push_back( object );
    }
    void Phicics_engine::remove_object( int index ) {

        SDL_Log("Removing object index %d", index );

        _objects[index]->_death_behavior( _objects[index], this );

        if( !_objects[index]->_is_dynamic )
            return;

        delete _objects[index];
        _objects.erase( _objects.begin() + index );
    }






}