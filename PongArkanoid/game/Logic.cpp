#include "SDLGame.h"
#include "Logic.h"
#include "Vector2D.h"
#include "GameMessage.h"
#include "NetClient.h"

Logic::Logic() : game_(nullptr){
    leftPaddle_ = new Paddle(PADDLE_MARGIN, SCREEN_HEIGHT * 0.5 - PADDLE_HEIGHT * 0.5, PADDLE_WIDTH, PADDLE_HEIGHT, Color(255, 255, 255));
    rightPaddle_ = new Paddle(SCREEN_WIDTH - PADDLE_MARGIN, SCREEN_HEIGHT * 0.5 - PADDLE_HEIGHT * 0.5, PADDLE_WIDTH, PADDLE_HEIGHT, Color(255, 255, 255));
}

Logic::Logic(SDLGame* game) : game_(game)
{
    leftPaddle_ = new Paddle(PADDLE_MARGIN, SCREEN_HEIGHT * 0.5 - PADDLE_HEIGHT * 0.5, PADDLE_WIDTH, PADDLE_HEIGHT, Color(255, 255, 255), game_);
    rightPaddle_ = new Paddle(SCREEN_WIDTH - PADDLE_MARGIN, SCREEN_HEIGHT * 0.5 - PADDLE_HEIGHT * 0.5, PADDLE_WIDTH, PADDLE_HEIGHT, Color(255, 255, 255), game_);
}

void Logic::Render(){
    leftPaddle_->Update();
    rightPaddle_->Update();
    auto it = bullets_.begin();
    while (it != bullets_.end())
    {
        bullets_[(*it).second->getBulletId()]->Update();
        it++;
    }
}

void Logic::Update()
{
    Render();
    
    Vector2D leftPos = leftPaddle_->getPos();
    Vector2D rightPos = rightPaddle_->getPos();

    auto it = bullets_.begin();
    while (it != bullets_.end())
    {
        int i = (*it).second->getBulletId();
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

        if(bullets_[i]->move())
        {
            delete bullets_[i];
            it = bullets_.erase(it);
        }
        else it++;            
    }
}

void Logic::movePaddle(int id, bool up)
{
    float vel = 0;
    if(up)
        vel = -PADDLE_VEL;
    else vel = PADDLE_VEL;

    Vector2D p (0, vel);

    // left paddle
    if(id == 0) p = p + leftPaddle_->getPos();
    else        p = p + rightPaddle_->getPos();
    
    MSGMovePaddle msg(p, id, game_->getClient()->getMatchId());
    game_->getClient()->send_Message(&msg);
}

void Logic::setPaddlePos(int id, Vector2D &pos){
    if(id == 0) leftPaddle_->setPos(pos);
    else        rightPaddle_->setPos(pos);
}

void Logic::shoot(int id, float x, float y)
{
    Bullet* b = nullptr;
    Vector2D pos;
    int d = (game_->getPlayerId() * 2 -1);
    if(id == 0) 
    {
        pos = leftPaddle_->getPos();
        pos.setX(pos.getX() + PADDLE_WIDTH);
    }
    else 
    {
        pos = rightPaddle_->getPos();
        pos.setX(pos.getX()  - (PADDLE_WIDTH + BULLET_SIZE) * d);
    }
    Vector2D dir (x - pos.getX(), y - pos.getY());

    MSGShoot msg(pos, dir, lastBulletId, game_->getClient()->getMatchId());
    game_->getClient()->send_Message(&msg);
    lastBulletId++;
}

void Logic::spawnBullet(Vector2D& pos, Vector2D& dir, size_t bulletID){
    Bullet* b = new Bullet(pos, dir, bulletID, BULLET_VEL, BULLET_SIZE, game_);
    bullets_[bulletID] = b;
}

size_t Logic::getLastBulletId(){
    return lastBulletId++;
}
