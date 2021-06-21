#include "SDLGame.h"
#include "Logic.h"

Logic::Logic(SDLGame* game)
{
    game_ = game;
    leftPaddle_ = new Paddle(PADDLE_MARGIN, SCREEN_HEIGHT * 0.5 - PADDLE_HEIGHT * 0.5, PADDLE_WIDTH, PADDLE_HEIGHT, Color(255, 255, 255), game_);
    rightPaddle_ = new Paddle(SCREEN_WIDTH - PADDLE_MARGIN, SCREEN_HEIGHT * 0.5 - PADDLE_HEIGHT * 0.5, PADDLE_WIDTH, PADDLE_HEIGHT, Color(255, 255, 255), game_);
}

void Logic::Update()
{
    leftPaddle_->Update();
    rightPaddle_->Update();
    
    std::pair<float, float> leftPos = leftPaddle_->getPos();
    std::pair<float, float> rightPos = rightPaddle_->getPos();

    int i = 0;
    while (i < bullets_.size())
    {
        if(bullets_[i]->collides(leftPos, PADDLE_WIDTH, PADDLE_HEIGHT))
        {
            bullets_[i]->bounce(true, true);
            printf("Player 2 wins\n");
        }
        else if(bullets_[i]->collides(rightPos, PADDLE_WIDTH, PADDLE_HEIGHT))
        {
            bullets_[i]->bounce(true, true);
            printf("Player 1 wins\n");
        }

        if(bullets_[i]->Update())
        {
            delete bullets_[i];
            bullets_.erase(bullets_.begin() + i);
        }

        else
            i++;            
    }
}

void Logic::movePaddle(int id, bool up)
{
    float vel = 0;
    if(up)
        vel = -PADDLE_VEL;
    else vel = PADDLE_VEL;

    // left paddle
    if(id == 0) leftPaddle_->move(vel);
    else        rightPaddle_->move(vel);
    
    
}

void Logic::shoot(int id, float x, float y)
{
    Bullet* b = nullptr;
    std::pair<float, float> pos;
    if(id == 0) 
    {
        pos = leftPaddle_->getPos();
        pos.first += PADDLE_WIDTH;
    }
    else 
    {
        pos = rightPaddle_->getPos();
        pos.first -= (PADDLE_WIDTH + BULLET_SIZE);
    }
    std::pair<float, float> dir {x - pos.first, y - pos.second};

    b = new Bullet(pos, dir, BULLET_VEL, BULLET_SIZE, game_);
    bullets_.push_back(b);

}
