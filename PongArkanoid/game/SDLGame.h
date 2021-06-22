#pragma once

#include <SDL.h>
#include <stdio.h>
#include <vector>

#include "Logic.h"

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

    Logic* logic_;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;

    //The surface contained by the window
    SDL_Surface* gScreenSurface = NULL;

    NetClient* client;

    int playerId = -1;

    bool init();
    void close();
public:
    SDLGame();
    SDLGame(const char * s, const char * p, const char *n = "Anonymous", int w = SCREEN_WIDTH, int h = SCREEN_HEIGHT);
    ~SDLGame();

    void run();

    void manageMsg(GameMessage* msg);

    SDL_Renderer* getRenderer() {return gRenderer;}

    inline Uint32 getTime() {
		return SDL_GetTicks();
	}

    int getPlayerId() {
		return playerId;
	}

    NetClient* getClient(){
        return client;
    }
};