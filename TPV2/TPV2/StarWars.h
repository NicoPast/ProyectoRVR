#pragma once

#include <vector>

#include "BulletsSystem.h"
#include "CollisionSystem.h"
#include "FightersSystem.h"
#include "GameCtrlSystem.h"
#include "NetworkingSystem.h"
#include "Manager.h"
#include "RenderSystem.h"
#include "SDLGame.h"

class StarWars {

public:
	StarWars(char* host, char* port, char* name);
	virtual ~StarWars();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame(char* name);
	void closeGame();

	SDLGame *game_;
	Manager *mngr_;
	bool exit_;

	char* host_;
	char* port_;

	NetworkingSystem* networkingSystem_;
	RenderSystem *renderSystem_;
	FightersSystem *fightersSystem_;
	GameCtrlSystem *gameCtrlSystem_;
	BulletsSystem *bulletsSystem_;
	CollisionSystem *collisionSystem_;

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

};
