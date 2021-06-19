#include "BulletsSystem.h"
#include "Manager.h"
#include "SDLGame.h"
#include "BulletsPool.h"
#include "Transform.h"

BulletsSystem::BulletsSystem() :
		System(ecs::_sys_Bullets) {
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double w, double h) {

	Entity *b = mngr_->addEntity<BulletsPool>(pos,vel,w,h);
	if (b != nullptr) {
		b->addToGroup(ecs::_grp_Bullets);
	}
	game_->getAudioMngr()->playChannel(Resources::Beat, 0);
}

void BulletsSystem::disableAll() {
	for (auto &b : mngr_->getGroupEntities(ecs::_grp_Bullets))
		b->setActive(false);
}

void BulletsSystem::update() {
	for (auto &e : mngr_->getGroupEntities(ecs::_grp_Bullets)) {
		Transform *tr = e->getComponent<Transform>(ecs::Transform);

		Vector2D p = tr->position_ + tr->velocity_;

		if ((p.getY() >= game_->getWindowHeight())
			|| (p.getY() + tr->height_ <= 0)) {
			tr->velocity_.setY(-tr->velocity_.getY());
		}
		if ((p.getX() >= game_->getWindowWidth())
			|| (p.getX() + tr->width_ <= 0)) {
			e->setActive(false);
		}

		tr->position_ = p;
	}
}

void BulletsSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_SHOOT: {
		const msg::Shoot& m = static_cast<const msg::Shoot&>(msg);
		shoot(m.pos, m.vel, m.w, m.h);
		break;
	}
	case msg::_START_ROUND: 
	case msg::_FIGHTER_DEATH: {
		disableAll();
		break;
	}
	case msg::_BULLET_INFO:{
		const msg::BulletInfo& m = static_cast<const msg::BulletInfo&>(msg);
		for (auto &e : mngr_->getGroupEntities(ecs::_grp_Bullets)) {
			if(m.id == e->getComponent<BulletInfo>(ecs::BulletInfo)->id_){
				auto bTR = e->getComponent<Transform>(ecs::Transform);
				bTR->position_ = m.pos;
				bTR->velocity_ = m.vel;
			}
		}
		break;
	}
	default:
		break;
	}
}

