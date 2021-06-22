#pragma once

#include <SDL.h>
#include <utility>

#include "Color.h"
#include "Vector2D.h"

class SDLGame;

class Paddle
{
private: 
    Color color_;
    SDLGame* game_;
    SDL_Rect paddle_;

    Vector2D position_;
    //std::pair<float, float> position_;
    float width_;
    float height_;
public:
    Paddle(float x, float y, float w, float h, Color c, SDLGame* g = nullptr): 
    width_(w), height_(h), color_(c), game_(g), position_(x, y)
    {        
        paddle_.x = x;
        paddle_.y = y;
        paddle_.w = w;
        paddle_.h = h;        
    }
    
    Paddle(){};
    ~Paddle(){};

    void Update();

    void move(float y);

    Vector2D& getPos(){return position_;}
    void setPos(Vector2D& pos){
        position_ = pos;
        paddle_.x = position_.getX();
        paddle_.y = position_.getY();
    }
};