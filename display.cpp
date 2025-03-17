//
// Created by Aron on 2025. 02. 09..
//

#include "display.h"
#include "global_variables.h"

#include <cstdio>









display::Screen::Screen( const char* title, int w, int h, Uint32 wf, Uint32 rf ){
    _wwidth = w;
    _wheight = h;

    _window = SDL_CreateWindow( title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, wf );
    if (_window == nullptr) {
        SDL_Log("[ERROR] (create window) %s", SDL_GetError());
        SDL_Quit();
        return;
    }

    _renderer = SDL_CreateRenderer(_window, -1, rf);
    if (_renderer == nullptr) {
        SDL_Log("[ERROR] (create renderer) %s", SDL_GetError());
        SDL_DestroyWindow(_window);
        SDL_Quit();
        return;
    }

}

display::Screen::~Screen() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();

    _renderer = nullptr;
    _window = nullptr;
}


bool display::Screen::is_open() const {
    return _renderer != nullptr  and  _window != nullptr;
}



void display::Screen::fill( display::Color_rgba c ) {
    SDL_SetRenderDrawColor( _renderer, c.r, c.g, c.b, c.a );
    SDL_RenderClear(_renderer);
}



static void draw_triangle(SDL_Renderer*, const display::Shape& );
static void draw_polygon(SDL_Renderer*, const display::Shape& );
static void draw_rectangle(SDL_Renderer*, const display::Shape&);
static void draw_circle(SDL_Renderer*, const display::Shape&);
void display::Screen::draw_shape( const display::Shape& shape ) {
    switch( shape._type ) {
        case 'r':
            draw_rectangle( _renderer, shape );
            break;
        case 'c':
            draw_circle( _renderer, shape );
            break;
        case 't':
            draw_triangle( _renderer, shape );
            break;
        case 'p':
            draw_polygon( _renderer, shape );
            break;
        default:
            break;
    }
}



void display::Screen::draw_shapes( const std::vector<display::Shape>& shapes ) {
    for( auto& shape : shapes ) {
        draw_shape( shape );
    }
}




void display::Screen::display() const {
    SDL_RenderPresent(_renderer);
}
















static void draw_triangle(SDL_Renderer* rendr, const display::Shape& shape) {
    SDL_Vertex vertices[3];
    for( int i = 0; i < 3; i++ ) {
        vertices[i].position.x = static_cast<float>(shape._points[i].x);
        vertices[i].position.y = static_cast<float>(shape._points[i].y);
        vertices[i].color.r = shape._color.r;
        vertices[i].color.g = shape._color.g;
        vertices[i].color.b = shape._color.b;
        vertices[i].color.a = shape._color.a;
    }

    SDL_RenderGeometry( rendr, nullptr, vertices, 3, nullptr, 0 );

}

static void draw_rectangle(SDL_Renderer* rendr, const display::Shape& shape) {
    SDL_Rect rect = {
        .x = shape._points[0].x,
        .y = shape._points[0].y,
        .w = shape._points[1].x,
        .h = shape._points[1].y
    };

    SDL_SetRenderDrawColor( rendr, shape._color.r, shape._color.g, shape._color.b, shape._color.a );
    SDL_RenderFillRect( rendr, &rect );
}

static void draw_circle(SDL_Renderer* rendr, const display::Shape& shape) {
    // TODO
}

static void draw_polygon(SDL_Renderer* rendr, const display::Shape& shape ) {
    auto vertices = new SDL_Vertex[shape._points.size()];
    for( int i = 0;   i < shape._points.size();   i++ ) {
        vertices[i].position.x = static_cast<float>(shape._points[i].x);
        vertices[i].position.y = static_cast<float>(shape._points[i].y);
        vertices[i].color.r = shape._color.r;
        vertices[i].color.g = shape._color.g;
        vertices[i].color.b = shape._color.b;
        vertices[i].color.a = shape._color.a;
    }

    SDL_RenderGeometry( rendr, nullptr, vertices, static_cast<int>(shape._points.size()), nullptr, 0 );

    delete[] vertices;

}



void display::Screen::update_size() const {
    static auto& width = global_variables::get_global_data().screen_width;
    static auto& height = global_variables::get_global_data().screen_height;

    SDL_GetWindowSize( _window, &width, &height );
}
