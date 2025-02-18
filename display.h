//
// Created by Aron on 2025. 02. 09..
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL.h>
#include <vector>




namespace display {


    struct Pixel_coord {
        int x;
        int y;
    };


    struct Color_rgba {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };



    struct Shape {
        char _type; // c: cicrle, r: rect, t: triangle
        Color_rgba _color;
        std::vector<Pixel_coord> _points;
    };/*
c:
    _points[0] = mid
    _points[1].x = radius
r: _points:  0:upperleft corner  1:width,height
t: _points:  0:3 corners
p: polygon
*/


    class Screen {
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        int _wwidth, _wheight;


        public:
        Screen( const char* title, int w, int h, Uint32 window_flag=SDL_WINDOW_SHOWN, Uint32 renderer_flag=SDL_RENDERER_ACCELERATED );
        ~Screen();

        bool is_open() const;

        void fill( Color_rgba color );

        void draw_shape( const Shape& shape );
        void draw_shapes( const std::vector<Shape>& shapes );

        void display();

    };


}



#endif //DISPLAY_H
