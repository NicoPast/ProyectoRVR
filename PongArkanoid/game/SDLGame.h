#pragma once

#include <SDL.h>
#include <stdio.h>
#include <vector>

#include "Color.h"
#include "Paddle.h"
#include "Bullet.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class NetClient;
class GameMessage;

class SDLGame {
private:
    //Screen dimension constants
    int screenW;
    int screenH;

    Paddle* leftPaddle;
    Paddle* rightPaddle;
    std::vector<Bullet*> bullets_;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;

    //The surface contained by the window
    SDL_Surface* gScreenSurface = NULL;
    //Key press surfaces constants
    enum KeyPressSurfaces
    {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };

    //The images that correspond to a keypress
    Color gKeyPressColors[ KEY_PRESS_SURFACE_TOTAL ];

    //Current displayed image
    Color* gCurrentColor = NULL;

    NetClient* client;

    int playerId = -1;

    bool loadColors();
    bool init();
    void close();
public:
    SDLGame();
    SDLGame(const char * s, const char * p, const char * n, int w, int h);
    ~SDLGame();

    void addBullet(Bullet* b);
    void run();

    void manageMsg(GameMessage* msg);


    SDL_Renderer* getRenderer() {return gRenderer;}
    
};