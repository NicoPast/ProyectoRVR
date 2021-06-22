#include "Paddle.h"
#include "SDLGame.h"

void Paddle::Update()
{
    SDL_SetRenderDrawColor( game_->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );		
    SDL_RenderFillRect( game_->getRenderer(), &paddle_ );
}

void Paddle::move(float y)
{
    position_.setY(position_.getY() + y);

    paddle_.y = position_.getY();
}
