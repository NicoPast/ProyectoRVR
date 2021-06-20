#include "StarWars.h"

#include "BulletsPool.h"
#include "SDL_macros.h"

using namespace std;

StarWars::StarWars(char* host, char* port, char* name) :
		host_(host), //
		port_(port), //
		exit_(false) { 
	initGame(name);
	cout << "TEST Constructor\n";
}

StarWars::~StarWars() {
	closeGame();
}

void StarWars::initGame(char* name) {

	game_ = SDLGame::init("Star Wars", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	if (!game_->getNetworking()->client(host_, port_)) {
		throw "Couldn`t connect to server!";
	}

	cout << "TEST Mngr y pool Init\n";

	mngr_ = new Manager(game_, name);

	cout << "TEST Pool Init\n";

	BulletsPool::init(100);

	cout << "TEST Systems Init\n";

	networkingSystem_ = mngr_->addSystem<NetworkingSystem>();
	fightersSystem_ = mngr_->addSystem<FightersSystem>();
	gameCtrlSystem_ = mngr_->addSystem<GameCtrlSystem>();
	bulletsSystem_ = mngr_->addSystem<BulletsSystem>();
	collisionSystem_ = mngr_->addSystem<CollisionSystem>();
	renderSystem_ = mngr_->addSystem<RenderSystem>();

	game_->getAudioMngr()->playMusic(Resources::ImperialMarch);
	cout << "TEST End Init\n";
}

void StarWars::closeGame() {
	delete mngr_;
}

void StarWars::start() {
	cout << "TEST start\n";

	exit_ = false;
	auto ih = InputHandler::instance();

	cout << "TEST start before while\n";

	while (!exit_) {

		cout << "TEST while start\n";

		Uint32 startTime = game_->getTime();
		SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
		SDL_RenderClear(game_->getRenderer());

		cout << "TEST while events\n";
		
		SDL_Event event;

		//While there's an event to handle
        while( SDL_PollEvent( &event ) )
        {
			ih->update(event);
			//If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                exit_ = true;
            }  

			if (ih->keyDownEvent()) {
				if (ih->isKeyDown(SDLK_ESCAPE)) {
					exit_ = true;
					break;
				}
			}
		}

		cout << "TEST while mngr ref\n";

		mngr_->refresh();

		cout << "TEST while before updates\n";

		gameCtrlSystem_->update();
		
		cout << "TEST while before fFpd\n";

		fightersSystem_->update();

		cout << "TEST while before bUpd\n";

		bulletsSystem_->update();

		cout << "TEST while before colUpd\n";

		if (collisionSystem_ != nullptr)
			collisionSystem_->update();

		cout << "TEST while before rUpd\n";

		renderSystem_->update();

		cout << "TEST while before flush\n";

		mngr_->flushMessages();

		cout << "TEST while before netSys update\n";

		networkingSystem_->update();

		cout << "TEST while before painting\n";

		SDL_RenderPresent(game_->getRenderer());
		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void StarWars::stop(){
	exit_ = true;
}