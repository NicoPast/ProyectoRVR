#include "Paddle.h"
#include "SDLGame.h"


void Bullet::bounce(bool hor, bool vert)
{
    bool bounced = false;

    if (vert)
        direction_.second *= -1.25f;

    if (hor)
        direction_.first *= -1.25f;



    if(hor || vert)
        collisionsLeft_ --;
}
bool Bullet::Update()
{
    position_.first +=  (vel_ * direction_.first);
    position_.second += (vel_ * direction_.second);

    bullet_.x = position_.first;
    bullet_.y = position_.second;

    SDL_SetRenderDrawColor( game_->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );		
    SDL_RenderFillRect( game_->getRenderer(), &bullet_ );
    
    bool v = (bullet_.y < 0 || bullet_.y + size_ > SCREEN_HEIGHT);
    bool h = (bullet_.x < 0 || bullet_.x + size_ > SCREEN_WIDTH);
    bounce(h, v);

    return collisionsLeft_ == 0;
}

bool Bullet::collides(std::pair<float, float> pos, float w, float h)
{
    return  position_.first < pos.first + w &&
            position_.first + size_ > pos.first &&
            position_.second < pos.second + h &&
            position_.second + size_ > pos.second;
}