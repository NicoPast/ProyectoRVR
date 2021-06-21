#include "Paddle.h"
#include "SDLGame.h"

void Paddle::Update()
{
    SDL_SetRenderDrawColor( game_->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );		
    SDL_RenderFillRect( game_->getRenderer(), &paddle_ );
}

void Paddle::move(float x, float y)
{
    x_ += x;
    y_ += y;

    paddle_.x = x_;
    paddle_.y = y_;
}