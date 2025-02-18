//
// Created by Aron on 2025. 02. 10..
//

#include <SDL.h>

#include "game_math.h"



void operator+=(game::Vector2& lhs, const game::Vector2& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
}
game::Vector2 operator+( const game::Vector2& lhs, const game::Vector2& rhs) {
    game::Vector2 result = lhs;
    result += rhs;
    return result;
}
void operator*=(game::Vector2& lhs, float rhs) {
    lhs.x *= rhs;
    lhs.y *= rhs;
}
game::Vector2 operator*( const game::Vector2& lhs, float rhs) {
    game::Vector2 result = lhs;
    result *= rhs;
    return result;
}
bool operator==( const game::Vector2& lhs, const game::Vector2& rhs) {
    return lhs.x == rhs.x  and  lhs.y == rhs.y;
}

float game::dist_pow2( const game::Vector2& a, const game::Vector2& b ) {
    const Vector2 diff = a + (b*-1.0f);
    return diff.x * diff.x + diff.y * diff.y;
}
float game::dist( const game::Vector2& a, const game::Vector2& b ) {
    const Vector2 diff = a + (b*-1.0f);
    return SDL_sqrtf( diff.x * diff.x + diff.y * diff.y );
}

game::Vector2 game::polar_to_vector2( float len, float dir ) {
    return {
        .x = len * SDL_cosf( dir ),
        .y = len * SDL_sinf( dir ),
    };
}

display::Pixel_coord game::vector2_to_pixel_coord( const Vector2& v ) {
    return { .x = static_cast<int>(v.x), .y = static_cast<int>(v.y) };
}









float game::line::crossing( const game::line::Line& l1, const game::line::Line& l2 ) {
    if( l1.slope == l2.slope ) {
        return 1.0f/0.0f;
    }

    return (l2.num - l1.num)/(l1.slope - l2.slope);
}


bool game::line::is_crossing( const game::line::Line& l1, const game::line::Line& l2 ) {
    if( l1.slope == l2.slope )
        return false;

    float cp = (l2.num - l1.num)/(l1.slope - l2.slope);

    float min = (l1.minp>l2.minp) ? l1.minp : l2.minp;
    float max = (l1.maxp<l2.maxp) ? l1.maxp : l2.maxp;

    if( cp > min && cp < max )
        return true;

    return false;

}