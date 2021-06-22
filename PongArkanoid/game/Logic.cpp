#include "SDLGame.h"
#include "Logic.h"
#include "Vector2D.h"
#include "GameMessage.h"
#include "NetClient.h"
#include "NetServer.h"

Logic::Logic(Match* m) : game_(nullptr), match_(m){
    leftPaddle_ = new Paddle(PADDLE_MARGIN, SCREEN_HEIGHT * 0.5 - PADDLE_HEIGHT * 0.5, PADDLE_WIDTH, PADDLE_HEIGHT, Color(255, 255, 255));
    rightPaddle_ = new Paddle(SCREEN_WIDTH - PADDLE_MARGIN, SCREEN_HEIGHT * 0.5 - PADDLE_HEIGHT * 0.5, PADDLE_WIDTH, PADDLE_HEIGHT, Color(255, 255, 255));
    blocks_ = new BlockWall(Vector2D(WALL_COLUMNS, WALL_ROWS));
}

Logic::Logic(SDLGame* game) : game_(game), match_(nullptr)
{
    leftPaddle_ = new Paddle(PADDLE_MARGIN, SCREEN_HEIGHT * 0.5 - PADDLE_HEIGHT * 0.5, PADDLE_WIDTH, PADDLE_HEIGHT, Color(255, 255, 255), game_);
    rightPaddle_ = new Paddle(SCREEN_WIDTH - PADDLE_MARGIN, SCREEN_HEIGHT * 0.5 - PADDLE_HEIGHT * 0.5, PADDLE_WIDTH, PADDLE_HEIGHT, Color(255, 255, 255), game_);
    blocks_ = new BlockWall(Vector2D(WALL_COLUMNS, WALL_ROWS), game);
}

void Logic::Render(){
    leftPaddle_->Update();
    rightPaddle_->Update();
    blocks_->Render();
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

    MoveBullets(1.0f);

    Collisions();
}

void Logic::UpdateClient()
{
    Render();

    MoveBullets(1.0f);
}

void Logic::UpdateServer(float t)
{
    MoveBullets(t);

    Collisions();
}

void Logic::MoveBullets(float t){
    auto it = bullets_.begin();
    while (it != bullets_.end())
    {
        bullets_[(*it).second->getBulletId()]->move(t);     
        it++;   
    }
}

void Logic::Collisions(){
    Vector2D leftPos = leftPaddle_->getPos();
    Vector2D rightPos = rightPaddle_->getPos();

    auto it = bullets_.begin();
    while (it != bullets_.end())
    {
        int i = (*it).second->getBulletId();
        if(bullets_[i]->collides(leftPos, PADDLE_WIDTH, PADDLE_HEIGHT))
        {
            bullets_[i]->bounce(true, true, match_);
            printf("Player 2 wins\n");
        }
        else if(bullets_[i]->collides(rightPos, PADDLE_WIDTH, PADDLE_HEIGHT))
        {
            bullets_[i]->bounce(true, true, match_);
            printf("Player 1 wins\n");
        }
        if(BlocksCollisions(i))
        {
            bullets_[i]->bounce(true, true, match_);
        }
        else if(bullets_[i]->wallsCollisions(match_))
        {
            delete bullets_[i];
            it = bullets_.erase(it);
            printf("Destroyed Bull %d\n", i);
        }
        else it++;   
    }
}

bool Logic::BlocksCollisions(int index)
{
    bool collides = false;

    int i = 0;
    while(i < WALL_ROWS && !collides)
    {
        int j = 0;
        while(j < WALL_COLUMNS && !collides)
        {
            Vector2D pos = {blocks_->GetBlock(i,j).x, blocks_->GetBlock(i,j).y};
            if(bullets_[index]->collides(pos, blocks_->GetBlock(i, j).w, blocks_->GetBlock(i, j).h)) collides = true;
            else j++;
        }
        i++;
    }
    return collides;
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

    dir = dir.normalize();

    MSGShoot msg(pos, dir, lastBulletId, 5, game_->getClient()->getMatchId());
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

void Logic::setBulletPos(int id, Vector2D &pos, Vector2D &dir, int bounces){
    if(bullets_.find(id) == bullets_.end()){
        Bullet* b = new Bullet(pos, dir, id, BULLET_VEL, BULLET_SIZE, game_);
        bullets_[id] = b;
    }
    if (bounces == 0){
        delete bullets_[id];
        bullets_.erase(id);
    }
    else bullets_[id]->updateBullet(pos, dir, bounces);
}
