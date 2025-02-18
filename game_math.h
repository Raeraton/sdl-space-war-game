//
// Created by Aron on 2025. 02. 10..
//

#ifndef GAME_MATH_H
#define GAME_MATH_H

#include "display.h"



namespace game {

    struct Vector2 {
        float x;
        float y;
    };


    float dist_pow2( const Vector2& a, const Vector2& b );  // dist 2  (faster to calculate)
    float dist( const Vector2& a, const Vector2& b );       // distance
    Vector2 polar_to_vector2( float len, float dir );
    display::Pixel_coord vector2_to_pixel_coord( const Vector2& v );



    namespace line {
        struct Line { // y = slope*x + num
            float slope;
            float num;
            float minp;
            float maxp;
        };

        float crossing( const Line& l1, const Line& l2 );  // x: slope1*x+a = slope2*x+b

        bool is_crossing( const Line& l1, const Line& l2 );
    }

}






void operator+=(game::Vector2& lhs, const game::Vector2& rhs);
game::Vector2 operator+( const game::Vector2& lhs, const game::Vector2& rhs);
void operator*=(game::Vector2& lhs, float rhs);
game::Vector2 operator*( const game::Vector2& lhs, float rhs);
bool operator==( const game::Vector2& lhs, const game::Vector2& rhs);


#endif //GAME_MATH_H
