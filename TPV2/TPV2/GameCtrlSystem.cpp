#include "GameCtrlSystem.h"

#include <string.h>

#include <cassert>
#include <cstdint>
#include "ecs.h"
#include "Entity.h"
#include "FighterInfo.h"
#include "FightersSystem.h"
#include "Manager.h"

using ecs::CmpId;

GameCtrlSystem::GameCtrlSystem() :
		System(ecs::_sys_GameCtrl),
		ready_(false){
	state_ = READY;
	resetScore();
}

void GameCtrlSystem::init() {
	state_ = READY;
	msg::PlayerInfo m(mngr_->getName());
	mngr_->send<msg::PlayerInfo>(mngr_->getName());
}

void GameCtrlSystem::update() {

	if (ready_ && state_ != RUNNING) {
		InputHandler *ih = game_->getInputHandler();
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
			mngr_->send<msg::Message>(msg::_START_REQ);
		}
	}
}

void GameCtrlSystem::recieve(const msg::Message& msg) {
	switch (msg.id)
	{
	case msg::_PLAYER_INFO: {
		if (ready_ || msg.senderClientId == mngr_->getClientId())
			return;

		ready_ = true;
		mngr_->setRivalName(static_cast<const msg::PlayerInfo&>(msg).name);
		mngr_->send<msg::PlayerInfo>(mngr_->getName());
		break;
	}
	case msg::_CLIENT_DISCONNECTED: {
		ready_ = false;
		score[0] = score[1] = 0;
		state_ = READY;
		break;
	}
	case msg::_START_REQ: {
		if (mngr_->getClientId() == 0 && state_ != RUNNING)
		{
			mngr_->send<msg::Message>(msg::_START_ROUND);
		}
		break;
	}
	case msg::_START_ROUND: {
		startGame();
		break;
	}
	case msg::_FIGHTER_DEATH: {
		onFighterDeath(static_cast<const msg::FighterDeath&>(msg).fighterID);
		break;
	}
	case msg::_BOTH_DIE: {
		bothDie();
		break;
	}
	default:
		break;
	}
}

void GameCtrlSystem::startGame() {
	if (state_ == GAMEOVER) {
		resetScore();
	}
	state_ = RUNNING;
}

void GameCtrlSystem::onFighterDeath(uint8_t fighterId) {
	assert(fighterId >= 0 && fighterId <= 1);

	uint8_t id = 1 - fighterId; // the id of the other player fighter

	game_->getAudioMngr()->playChannel(Resources::Explosion, 0);

	state_ = ROUNDOVER;
	score[id]++;
	if (score[id] == 3) {
		if (fighterId == mngr_->getClientId())
			game_->getAudioMngr()->playChannel(Resources::Cheer, 0);
		else game_->getAudioMngr()->playChannel(Resources::Boooo, 0);
		state_ = GAMEOVER;
	}

}

void GameCtrlSystem::bothDie() {
	state_ = ROUNDOVER;
	game_->getAudioMngr()->playChannel(Resources::Explosion, 0);
}

void GameCtrlSystem::resetScore() {
	score[0] = score[1] = 0;
}
