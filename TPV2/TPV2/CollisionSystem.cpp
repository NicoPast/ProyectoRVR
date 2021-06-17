#include "CollisionSystem.h"

#include "Collisions.h"
#include "BulletsSystem.h"
#include "FighterInfo.h"
#include "GameCtrlSystem.h"
#include "Transform.h"
#include "Manager.h"

CollisionSystem::CollisionSystem() :
		System(ecs::_sys_Collision) {
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::update() {
	auto gameCtrlSys = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	if (mngr_->getClientId() == 1 || gameCtrlSys->getState() != GameCtrlSystem::RUNNING)
		return;


	bool roundOver = false;

	vector<Transform*> fs;

	for (auto &f : mngr_->getGroupEntities(ecs::_grp_Fighters)) {

		auto fTR = f->getComponent<Transform>(ecs::Transform);
		fs.push_back(fTR);

		for (auto &b : mngr_->getGroupEntities(ecs::_grp_Bullets)) {
			if (!b->isActive())
				continue;
		

			auto bTR = b->getComponent<Transform>(ecs::Transform);

			if (Collisions::collidesWithRotation(bTR->position_, bTR->width_,
					bTR->height_, bTR->rotation_, fTR->position_, fTR->width_,
					fTR->height_, fTR->rotation_)) {

				//roundOver = true;
				//auto id = f->getComponent<FighterInfo>(ecs::FighterInfo)->fighterId;
				//mngr_->send<msg::FighterDeath>(id);

				cout << "colision\n";

				bTR->velocity_.setX(-bTR->velocity_.getX());
			}
		}
	}

	if (Collisions::collidesWithRotation(fs[0]->position_, fs[0]->width_,
		fs[0]->height_, fs[0]->rotation_, fs[1]->position_, fs[1]->width_,
		fs[1]->height_, fs[1]->rotation_)) {

		roundOver = true;
		mngr_->send<msg::Message>(msg::_BOTH_DIE);
	}
}

