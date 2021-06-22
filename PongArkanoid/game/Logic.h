#pragma once

#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <map>

#include "Color.h"
#include "Paddle.h"
#include "Bullet.h"

const float PADDLE_MARGIN = 50;
const float PADDLE_HEIGHT = 50;
const float PADDLE_WIDTH = 10;
const float PADDLE_VEL = 5.0f;

const float BULLET_SIZE = 20;
const float BULLET_VEL = 2.5f;

class SDLGame;

class Logic {

private:    
    SDLGame* game_;
    Paddle* leftPaddle_;
    Paddle* rightPaddle_;
    //std::vector<Bullet*> bullets_;
    std::map<size_t, Bullet*> bullets_;

    size_t lastBulletId = 0;

public:
    Logic(SDLGame* game);
    ~Logic(){}

    void Render();
    void Update();
    void movePaddle(int id, bool up);
    void shoot(int id, float x, float y);
};