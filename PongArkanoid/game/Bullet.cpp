#include <stdio.h>
#include "Paddle.h"
#include "SDLGame.h"


void Bullet::bounce()
{
    bool bounced = false;

    if (bullet_.y < 0 || bullet_.y + SIZE_ > SCREEN_HEIGHT)
    {
        direction_.second *= -1.25f;
        bounced = true;
    }   

    if (bullet_.x < 0 || bullet_.x + SIZE_ > SCREEN_WIDTH)
    {
        direction_.first *= -1.25f;
        bounced = true;
    }

    if(bounced)
        collisionsLeft_ --;
}
bool Bullet::Update()
{
    position_.first +=  (VEL_ * direction_.first);
    position_.second += (VEL_ * direction_.second);

    bullet_.x = position_.first;
    bullet_.y = position_.second;

    SDL_SetRenderDrawColor( game_->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );		
    SDL_RenderFillRect( game_->getRenderer(), &bullet_ );

    bounce();

    return collisionsLeft_ == 0;
}

bool Bullet::collides(std::pair<float, float> pos, float w, float h)
{
    return  position_.first < pos.first + w &&
            position_.first + SIZE_ > pos.first &&
            position_.second < pos.second + h &&
            position_.second + SIZE_ > pos.second;
}