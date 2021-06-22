#include "Paddle.h"
#include "SDLGame.h"

void Paddle::Update()
{
    SDL_SetRenderDrawColor( game_->getRenderer(), color_.r, color_.g, color_.b, 255);		
    SDL_RenderFillRect( game_->getRenderer(), &paddle_ );
}

void Paddle::move(float y)
{
    position_.setY(position_.getY() + y);

    paddle_.y = position_.getY();
}
