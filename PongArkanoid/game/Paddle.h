#pragma once

#include <SDL.h>
#include <utility>
#include "Color.h"

class SDLGame;

class Paddle
{
private: 
    Color color_;
    SDLGame* game_;
    SDL_Rect paddle_;

    std::pair<float, float> position_;
    float width_;
    float height_;
public:
    Paddle(float x, float y, float w, float h, Color c, SDLGame* g): 
    width_(w), height_(h), color_(c), game_(g)
    {
        position_.first = x;
        position_.second = y;
        
        paddle_.x = x;
        paddle_.y = y;
        paddle_.w = w;
        paddle_.h = h;        
    }
    
    Paddle(){};
    ~Paddle(){};

    void Update();

    void move(float x, float y);
    void shoot(float x, float y);
};