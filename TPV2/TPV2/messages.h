#pragma once
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "Vector2D.h"

namespace msg {

	using msgSizeType = uint32_t;

	enum MsgId : uint8_t {
		_CONNECTED, //
		_CONNECTION_REFUSED, //
		_CLIENT_DISCONNECTED, //
		_PLAYER_INFO, //
		_FIGHTER_INFO, //
		_START_REQ, //
		_START_ROUND, //
		_SHOOT, //
		_FIGHTER_DEATH, //
		_BOTH_DIE, //

		//
		_last_MsgId_
	};

	#pragma pack(push,1)

	struct Message {
		Message(msgSizeType size, MsgId id) :
				size(size), senderClientId(0), id(id) {
		}
		Message(MsgId id) :
				Message(sizeof(Message), id) {
		}
		msgSizeType size;
		uint32_t senderClientId;
		MsgId id;
	};

	struct ConnectedMsg: Message {
		ConnectedMsg(int clientId) :
				Message(sizeof(ConnectedMsg), _CONNECTED), clientId(clientId) {
		}
		uint32_t clientId;
	};

	struct ClientDisconnectedMsg: Message {
		ClientDisconnectedMsg(uint32_t clientId) :
				Message(sizeof(ClientDisconnectedMsg), _CLIENT_DISCONNECTED), clientId(clientId) {
		}
		uint32_t clientId;
	};

	struct PlayerInfo : Message {
		PlayerInfo(const char* n) :
			Message(sizeof(PlayerInfo), _PLAYER_INFO) {
			strcpy_s(&name[0], 11, n);
		}
		char name[11];
	};


	struct FighterInfo : Message {
		FighterInfo(double x, double y, double rot) :
			Message(sizeof(FighterInfo), _FIGHTER_INFO), x(x), y(y), rot(rot) {

		}
		double x;
		double y;
		double rot;
	};

	struct Shoot : Message {
		Shoot(Vector2D p, Vector2D v, double w, double h) : 
			Message(sizeof(Shoot), _SHOOT), pos(p), vel(v), w(w), h(h) {

		}

		Vector2D pos;
		Vector2D vel;
		double w;
		double h;
	};

	struct FighterDeath : Message {
		FighterDeath(uint32_t fID) :
			Message(sizeof(FighterDeath), _FIGHTER_DEATH), fighterID(fID) {

		}

		uint32_t fighterID;
	};

#pragma pack(pop)
}
