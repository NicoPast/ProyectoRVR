#include "StarWars.h"

#include "BulletsPool.h"
#include "SDL_macros.h"

using namespace std;

StarWars::StarWars(char* host, int port, char* name) :
		host_(host), //
		port_(port), //
		exit_(false) { 
	initGame(name);
}

StarWars::~StarWars() {
	closeGame();
}

void StarWars::initGame(char* name) {

	game_ = SDLGame::init("Star Wars", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	if (!game_->getNetworking()->client(host_, port_)) {
		throw "Couldn`t connect to server!";
	}

	mngr_ = new Manager(game_, name);

	BulletsPool::init(100);

	networkingSystem_ = mngr_->addSystem<NetworkingSystem>();
	fightersSystem_ = mngr_->addSystem<FightersSystem>();
	gameCtrlSystem_ = mngr_->addSystem<GameCtrlSystem>();
	bulletsSystem_ = mngr_->addSystem<BulletsSystem>();
	collisionSystem_ = mngr_->addSystem<CollisionSystem>();
	renderSystem_ = mngr_->addSystem<RenderSystem>();

	game_->getAudioMngr()->playMusic(Resources::ImperialMarch);
}

void StarWars::closeGame() {
	delete mngr_;
}

void StarWars::start() {
	exit_ = false;
	auto ih = InputHandler::instance();

	while (!exit_) {
		Uint32 startTime = game_->getTime();
		SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
		SDL_RenderClear(game_->getRenderer());

		ih->update();
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(SDLK_ESCAPE)) {
				exit_ = true;
				break;
			}
		}

		mngr_->refresh();

		gameCtrlSystem_->update();
		fightersSystem_->update();
		bulletsSystem_->update();
		if (collisionSystem_ != nullptr)
			collisionSystem_->update();
		renderSystem_->update();

		mngr_->flushMessages();
		networkingSystem_->update();

		SDL_RenderPresent(game_->getRenderer());
		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

