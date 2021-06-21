#pragma once

#include <SDL.h>
#include <utility>
#include <math.h>
#include "Color.h"

class SDLGame;

class Bullet
{
private:
    SDLGame* game_;
    SDL_Rect bullet_;

    int collisionsLeft_ = 5;
    const float VEL_ = 1.0f;
    const float SIZE_ = 20.0f;

    std::pair<float, float> position_;
    std::pair<float, float> direction_;

    void bounce();

public:
    Bullet();
    Bullet(std::pair<float, float> pos, std::pair<float, float> dir, SDLGame* g): direction_(dir), game_(g)
    {
        float inv_length = 1.0f / sqrt(dir.first * dir.first + dir.second * dir.second);
        direction_.first = dir.first * inv_length;
        direction_.second = dir.second * inv_length;
        
        position_.first = pos.first;
        position_.second = pos.second;

        bullet_.x = pos.first;
        bullet_.y = pos.second;
        bullet_.w = SIZE_;
        bullet_.h = SIZE_;
    };

    ~Bullet(){};
    bool Update();
    
    bool collides(std::pair<float, float> pos, float w, float h);
    

};