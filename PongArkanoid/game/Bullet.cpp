#include "Paddle.h"
#include "SDLGame.h"
#include "NetServer.h"


void Bullet::bounce(bool hor, bool vert, Match* m)
{
    bool bounced = false;

    if (vert)
        direction_.setY(direction_.getY() * -1.25f);

    if (hor)
        direction_.setX(direction_.getX() * -1.25f);

    if(hor || vert)
        collisionsLeft_ --;

    if(m){
        //m->clients
    }
}
void Bullet::Update()
{
    SDL_SetRenderDrawColor( game_->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );		
    SDL_RenderFillRect( game_->getRenderer(), &bullet_ );
}

bool Bullet::collides(Vector2D pos, float w, float h)
{
    return  position_.getX() < pos.getX() + w &&
            position_.getX() + size_ > pos.getX() &&
            position_.getY() < pos.getY() + h &&
            position_.getY() + size_ > pos.getY();
}

void Bullet::move(){
    position_ = position_ + (direction_.normalize() * vel_);
}

bool Bullet::wallsCollisions(){
    bullet_.x = position_.getX();
    bullet_.y = position_.getY();

    bool v = (bullet_.y < 0 || bullet_.y + size_ > SCREEN_HEIGHT);
    bool h = (bullet_.x < 0 || bullet_.x + size_ > SCREEN_WIDTH);
    bounce(h, v);

    return collisionsLeft_ == 0;
}

void Bullet::updateBullet(Vector2D& pos, Vector2D& dir, int bounces){    
    position_ = pos;
    direction_ = dir;
    collisionsLeft_ = bounces;
}