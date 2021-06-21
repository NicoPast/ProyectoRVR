#pragma once

#include <SDL.h>
#include <stdio.h>

#include "Color.h"

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

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
        
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

    bool loadColors();
    bool init();
    void close();
public:
    SDLGame();
    SDLGame(const char * s, const char * p, const char * n, int w, int h);
    ~SDLGame();

    void run();

    void manageMsg(GameMessage* msg);
};