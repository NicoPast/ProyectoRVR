#include "Paddle.h"
#include "SDLGame.h"

void Bullet::Update()
{
    position_.first +=  (VEL_ * direction_.first);
    position_.second += (VEL_ * direction_.second);

    bullet_.x = position_.first;
    bullet_.y = position_.second;

    SDL_SetRenderDrawColor( game_->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );		
    SDL_RenderFillRect( game_->getRenderer(), &bullet_ );
}

bool Bullet::collides(std::pair<float, float> pos, float w, float h)
{
    return  position_.first < pos.first + w &&
            position_.first + SIZE_ > pos.first &&
            position_.second < pos.second + h &&
            position_.second + SIZE_ > pos.second;
}