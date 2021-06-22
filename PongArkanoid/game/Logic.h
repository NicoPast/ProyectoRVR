#pragma once

#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <map>

#include "Color.h"
#include "Paddle.h"
#include "Bullet.h"
#include "BlockWall.h"

class Match;

const float PADDLE_MARGIN = 50;
const float PADDLE_HEIGHT = 50;
const float PADDLE_WIDTH = 10;
const float PADDLE_VEL = 5.0f;

const float BULLET_SIZE = 20;
const float BULLET_VEL = 2.5f;
const float WALL_SIZE = 25;
const float WALL_MARGIN = 7.5f;
const int WALL_ROWS = 12;
const int WALL_COLUMNS = 5;

class SDLGame;

class Logic {

private:    
    SDLGame* game_;
    Match* match_;
    Paddle* leftPaddle_;
    Paddle* rightPaddle_;
    BlockWall* blocks_;
    //std::vector<Bullet*> bullets_;
    std::map<size_t, Bullet*> bullets_;

    size_t lastBulletId = 0;

public:
    // usado por el server
    Logic(Match* m);
    // usado por el cliente
    Logic(SDLGame* game);
    ~Logic(){}

    void Render();
    void Update();

    void UpdateClient();
    void UpdateServer(float t);

    void Collisions();
    bool BlocksCollisions(int index);

    void MoveBullets(float t);
    
    // cliente envia señal
    void movePaddle(int id, bool up);

    void setPaddlePos(int id, Vector2D &pos);
    
    // cliente envia señal
    void shoot(int id, float x, float y);

    void spawnBullet(Vector2D& pos, Vector2D& dir, size_t bulletID);

    void setBulletPos(int id, Vector2D &pos, Vector2D &dir, int bounces);

    size_t getLastBulletId();
};