#pragma once

#include <SDL.h>
#include "Color.h"

class SDLGame;

class Paddle
{
private: 
    Color color_;
    SDLGame* game_;
    SDL_Rect paddle_;

    float x_;
    float y_;
    float width_;
    float height_;
public:
    Paddle(float x, float y, float w, float h, Color c, SDLGame* g): 
    x_(x), y_(y), width_(w), height_(h), color_(c), game_(g)
    {
        paddle_.x = x;
        paddle_.y = y;
        paddle_.w = w;
        paddle_.h = h;        
    }
    
    Paddle(){};
    ~Paddle(){};

    void Update();

    void move(float x, float y);
};