#include "engine.h"

#include <bits/streambuf_iterator.h>

#include "global_variables.h"




namespace game::engine {



    void Object::accelerate( const Vector2& acceleration ) {
        _velocity += acceleration * global_variables::get_deltatime();
    }

    void Object::rotate( float r ) {
        _angular_velocity += r * global_variables::get_deltatime();
    }

    void Object::update() {
        float delta_time = global_variables::get_deltatime();
        _position += _velocity * delta_time;
        _direction += _angular_velocity * delta_time;
    }



    bool test_for_collision( const Object& obj1, const Object& obj2 ) {
        // TODO optimise sqrt
        float max_radius = obj1.get_radius() + obj2.get_radius();

        if( max_radius > dist( obj1._position, obj2._position ) )
            return true;
        return false;
    }








    void Phicics_engine::update_objects() {
        for( auto& object : _objects ) {
            if( object->_is_existing ) {
                object->update();
            }
        }
    }


    void Phicics_engine::handle_collisions() {
        for(int i=0;  i<_objects.size(); i++) {
            if( !_objects[i]->_is_existing )
                continue;

            for(int j=i+1;  j<_objects.size();  j++) {
                if( !_objects[j]->_is_existing )
                    continue;

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
            if( !_objects[i]->_is_existing  ) {
                remove_object( i );
            }
        }
    }


    void Phicics_engine::add_object( Object* object ) {
        _objects.push_back( object );
    }
    void Phicics_engine::remove_object( int index ) {
        if( !_objects[index]->_is_dynamic )
            return;

        delete _objects[index];
        _objects.erase( _objects.begin() + index );
    }






}