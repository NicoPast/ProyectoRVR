#include "NetworkingSystem.h"

#include "messages.h"
#include "Manager.h"

NetworkingSystem::NetworkingSystem() :
		System(ecs::_sys_NetWorking) {

}

NetworkingSystem::~NetworkingSystem() {
}

void NetworkingSystem::recieve(const msg::Message &msg) {
	if (msg.senderClientId == mngr_->getClientId()) {
		game_->getNetworking()->send(msg);
	}
}

void NetworkingSystem::update() {
	auto net = game_->getNetworking();
	msg::Message *msg = nullptr;

	while ((msg = net->recieve()) != nullptr) {
		switch (msg->id) {
		case msg::_CLIENT_DISCONNECTED:
			mngr_->forwardMsg<msg::ClientDisconnectedMsg>(msg->senderClientId,
					static_cast<msg::ClientDisconnectedMsg*>(msg)->clientId);
			break;
		case msg::_PLAYER_INFO: {
			msg::PlayerInfo* m = static_cast<msg::PlayerInfo*>(msg);
			mngr_->forwardMsg<msg::PlayerInfo>(msg->senderClientId, m->name);
			break;
		}
		case msg::_FIGHTER_INFO: {
			msg::FighterInfo* m = static_cast<msg::FighterInfo*>(msg);
			mngr_->forwardMsg<msg::FighterInfo>(msg->senderClientId, m->x, m->y, m->rot);
			break;
		}
		case msg::_START_REQ: {
			mngr_->forwardMsg<msg::Message>(msg->senderClientId, msg::_START_REQ);
			break;
		}
		case msg::_START_ROUND: {
			mngr_->forwardMsg<msg::Message>(msg->senderClientId, msg::_START_ROUND);
			break;
		}
		case msg::_SHOOT: {
			msg::Shoot* m = static_cast<msg::Shoot*>(msg);
			mngr_->forwardMsg<msg::Shoot>(msg->senderClientId, m->pos, m->vel, m->w, m->h);
			break;
		}
		case msg::_FIGHTER_DEATH:{
			msg::FighterDeath* m = static_cast<msg::FighterDeath*>(msg);
			mngr_->forwardMsg<msg::FighterDeath>(msg->senderClientId, m->fighterID);
			break;
		}
		case msg::_BOTH_DIE:{
			mngr_->forwardMsg<msg::Message>(msg->senderClientId, msg::_BOTH_DIE);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

}
