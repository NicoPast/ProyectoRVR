#include "Paddle.h"
#include "SDLGame.h"

void Paddle::Update()
{
    SDL_SetRenderDrawColor( game_->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );		
    SDL_RenderFillRect( game_->getRenderer(), &paddle_ );
}

void Paddle::move(float x, float y)
{
    position_.first += x;
    position_.second += y;

    paddle_.x = position_.first;
    paddle_.y = position_.second;
}

void Paddle::shoot(float x, float y)
{
    std::pair<float, float> dir {x - position_.first, y - position_.second};

    game_->addBullet(new Bullet(position_,dir, game_));
}