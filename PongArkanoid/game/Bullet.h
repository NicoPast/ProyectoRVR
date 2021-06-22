#pragma once

#include <SDL.h>
#include <utility>
#include <math.h>

#include "Color.h"
#include "Vector2D.h"

class SDLGame;

class Bullet
{
private:
    SDLGame* game_;
    SDL_Rect bullet_;

    int collisionsLeft_ = 5;
    double vel_;
    float size_;
    Vector2D position_;
    Vector2D direction_;

    size_t id;
public:
    Bullet();
    Bullet(Vector2D pos, Vector2D dir, size_t id, float v, float s, SDLGame* g): 
    direction_(dir), position_(pos), id(id), game_(g), vel_(v), size_(s)
    {
        float inv_length = 1.0f / sqrt(dir.getX() * dir.getX() + dir.getY() * dir.getY());
        direction_.setX(dir.getX() * inv_length);
        direction_.setY(dir.getY() * inv_length);

        bullet_.x = pos.getX();
        bullet_.y = pos.getY();
        bullet_.w = size_;
        bullet_.h = size_;
    };

    ~Bullet(){};
    void Update();
    
    void bounce(bool hor, bool vert);
    bool collides(Vector2D pos, float w, float h);
    
    bool move();

    size_t getBulletId(){ return id;};
};