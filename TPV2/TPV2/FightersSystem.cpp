#include "ecs.h"
#include "Manager.h"
#include "Entity.h"
#include "Transform.h"
#include "Image.h"
#include "CtrlKeys.h"
#include "BulletsSystem.h"
#include "FighterInfo.h"
#include "FightersSystem.h"
#include "GameCtrlSystem.h"

#include <cstdint>
#include <algorithm>

using ecs::CmpId;

FightersSystem::FightersSystem() :
		System(ecs::_sys_Fighters), fighter0_(nullptr), fighter1_(nullptr) {
}

FightersSystem::~FightersSystem() {
}

void FightersSystem::resetFighterPositions() {
	auto f0Tr = fighter0_->getComponent<Transform>(ecs::Transform);
	f0Tr->velocity_ = Vector2D(0.0, 0.0);
	f0Tr->position_ = Vector2D(10, game_->getWindowHeight() / 2 - 25);
	f0Tr->rotation_ = 90.0;

	auto f1Tr = fighter1_->getComponent<Transform>(ecs::Transform);
	f1Tr->velocity_ = Vector2D(0.0, 0.0);
	f1Tr->position_ = Vector2D(game_->getWindowWidth() - 50.0 - 10.0,
			game_->getWindowHeight() / 2 - 25);
	f1Tr->rotation_ = -90.0;
}

void FightersSystem::init() {

	// left fighter
	fighter0_ = mngr_->addEntity();
	auto f0Tr = fighter0_->addComponent<Transform>();
	f0Tr->position_ = Vector2D(10, game_->getWindowHeight() / 2 - 25);
	f0Tr->velocity_ = Vector2D(0.0, 0.0);
	f0Tr->width_ = 50.0;
	f0Tr->height_ = 50.0;
	f0Tr->rotation_ = 90.0;
	//fighter0_->addComponent<CtrlKeys>(SDLK_a, SDLK_d, SDLK_w, SDLK_s, SDLK_e);
	fighter0_->addComponent<CtrlKeys>(SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN, SDLK_SPACE);

	fighter0_->addComponent<Image>(
			game_->getTextureMngr()->getTexture(Resources::Fighter));
	fighter0_->addToGroup(ecs::_grp_Fighters);
	mngr_->setHandler(ecs::_hdlr_Fighter0, fighter0_);
	fighter0_->addComponent<FighterInfo>(0);

	// right fighter
	fighter1_ = mngr_->addEntity();
	auto f1Tr = fighter1_->addComponent<Transform>();
	f1Tr->position_ = Vector2D(game_->getWindowWidth() - 50.0 - 10.0,
			game_->getWindowHeight() / 2 - 25);
	f1Tr->velocity_ = Vector2D(0.0, 0.0);
	f1Tr->width_ = 50.0;
	f1Tr->height_ = 50.0;
	f1Tr->rotation_ = -90.0;
	//fighter1_->addComponent<CtrlKeys>(SDLK_a, SDLK_d, SDLK_w, SDLK_s, SDLK_e);
	fighter1_->addComponent<CtrlKeys>(SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN, SDLK_SPACE);

	fighter1_->addComponent<Image>(
			game_->getTextureMngr()->getTexture(Resources::Fighter));
	fighter1_->addToGroup(ecs::_grp_Fighters);
	fighter1_->addComponent<FighterInfo>(1);
	mngr_->setHandler(ecs::_hdlr_Fighter1, fighter1_);
}

void FightersSystem::update() {
	auto gameState =
			mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->getState();
	if (gameState != GameCtrlSystem::RUNNING)
		return;
	if(mngr_->getClientId() == 0)
		updateFighter(fighter0_);
	else updateFighter(fighter1_);

}

void FightersSystem::recieve(const msg::Message& msg)
{
	Transform* tr = nullptr;
	switch (msg.id)
	{
		
	case msg::_FIGHTER_INFO: {
		if (msg.senderClientId == mngr_->getClientId())
			return;

		const msg::FighterInfo& m = static_cast<const msg::FighterInfo&>(msg);

		if (msg.senderClientId == 0) {
			tr = mngr_->getHandler(ecs::_hdlr_Fighter0)->getComponent<Transform>(ecs::Transform);
		}
		else {
			tr = mngr_->getHandler(ecs::_hdlr_Fighter1)->getComponent<Transform>(ecs::Transform);
		}
		tr->position_ = { m.x, m.y };
		tr->rotation_ = m.rot;
		break;
	}
	case msg::_START_ROUND: {
		resetFighterPositions();
		break;
	}
	default:
		break;
	}
}

void FightersSystem::updateFighter(Entity *e) {
	Transform *tr = e->getComponent<Transform>(ecs::Transform);
	CtrlKeys *keys = e->getComponent<CtrlKeys>(ecs::CtrlKeys);

	auto ih = game_->getInputHandler();
	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(keys->left)) { // turn left
			tr->rotation_ = fmod(tr->rotation_ - 5.0, 360.0);
			tr->velocity_ = tr->velocity_.rotate(-5.0);
		} else if (ih->isKeyDown(keys->right)) { // turn right
			tr->rotation_ = fmod(tr->rotation_ + 5.0, 360.0);
			tr->velocity_ = tr->velocity_.rotate(5.0);
		} else if (ih->isKeyDown(keys->speedup)) { // speed up
			tr->velocity_ = Vector2D(0.0, -1.0).rotate(tr->rotation_)
					* (std::min(tr->velocity_.magnitude() + 0.2, 3.0));
		} else if (ih->isKeyDown(keys->slowdown)) { // slow down
			tr->velocity_ = Vector2D(0.0, -1.0).rotate(tr->rotation_)
					* (std::max(tr->velocity_.magnitude() - 0.2, 0.0));
		} else if (ih->isKeyDown(keys->shoot)
				&& game_->getTime() - keys->lastShootTime > 1000) { // shoot
			keys->lastShootTime = game_->getTime();
			Vector2D p = tr->position_
					+ Vector2D(tr->width_ / 2, tr->height_ / 2)
					+ Vector2D(0, -(tr->height_ / 2 + 5.0)).rotate(
							tr->rotation_);
			Vector2D d = Vector2D(0, -1).rotate(tr->rotation_) * 2;

			mngr_->send<msg::Shoot>(p, d, 2, 5);
		}
	}

	// motion
	Vector2D oldPos = tr->position_;
	Vector2D newPos = tr->position_ + tr->velocity_;

	tr->position_ = newPos;
	tr->velocity_ = tr->velocity_ * 0.995;

	double y = newPos.getY();
	double x = newPos.getX();

	if (y <= 0 || y + tr->height_ >= game_->getWindowHeight() || x <= 0
			|| x + tr->width_ >= game_->getWindowWidth()) {
		tr->velocity_ = Vector2D();
		tr->position_ = oldPos;
	}

	mngr_->send<msg::FighterInfo>(tr->position_.getX(), tr->position_.getY(), tr->rotation_);
}
