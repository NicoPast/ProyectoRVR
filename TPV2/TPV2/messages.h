#pragma once
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>

#include "Vector2D.h"
#include "Serializable.h"

namespace msg {

	using msgSizeType = uint32_t;

	enum MsgId : uint8_t {
		_CONNECTED, //
		_CONNECTION_REFUSED, //
		_CLIENT_DISCONNECTED, //
		_PLAYER_INFO, //
		_FIGHTER_INFO, //
		_BULLET_INFO, //
		_START_REQ, //
		_START_ROUND, //
		_SHOOT, //
		_FIGHTER_DEATH, //
		_BOTH_DIE, //

		//
		_last_MsgId_
	};

	#pragma pack(push,1)

	struct Message : public Serializable{
		Message(msgSizeType size, MsgId id) :
				size(size), senderClientId(0), id(id) {
		}
		Message(MsgId id) :
				Message(sizeof(Message), id) {
		}
		virtual void to_bin() {
		}

		virtual int from_bin(char * data) {
			return 0;
		}
		msgSizeType size;			// creo que no
		uint32_t senderClientId;	// hacen falta
		MsgId id;
	};

	struct ConnectedMsg: Message {
		ConnectedMsg(int clientId) :
				Message(sizeof(ConnectedMsg), _CONNECTED), clientId(clientId) {
		}
		virtual void to_bin() override {
			//estos creo que no hacen falta pero los meto por si acaso
			size_t sz = sizeof(ConnectedMsg);
			memcpy(_data, &size, sz);
			size_t offset = sz;

			sz = sizeof(uint32_t);
			memcpy(_data + offset, &senderClientId, sz);
			offset += sz;

			// hasta aqui los no necesarios

			sz = sizeof(MsgId);
			memcpy(_data + offset, &id, sz);
			offset += sz;

			sz = sizeof(uint32_t);
			memcpy(_data + offset, &clientId, sz);
		}

		virtual int from_bin(char * data) override {

			//estos creo que no hacen falta pero los meto por si acaso
			size_t sz = sizeof(ConnectedMsg);
			memcpy(&size, _data, sz);
			size_t offset = sz;

			sz = sizeof(uint32_t);
			memcpy(&senderClientId, _data + offset, sz);
			offset += sz;

			// hasta aqui los no necesarios

			sz = sizeof(MsgId);
			memcpy(&id, _data + offset, sz);
			offset += sz;

			sz = sizeof(uint32_t);
			memcpy(&clientId, _data + offset, sz);
			return 0;
		}
		uint32_t clientId;
	};

	struct ClientDisconnectedMsg: Message {
		ClientDisconnectedMsg(uint32_t clientId) :
				Message(sizeof(ClientDisconnectedMsg), _CLIENT_DISCONNECTED), clientId(clientId) {
		}
		virtual void to_bin() override {
			//estos creo que no hacen falta pero los meto por si acaso
			size_t sz = sizeof(ClientDisconnectedMsg);
			memcpy(_data, &size, sz);
			size_t offset = sz;

			sz = sizeof(uint32_t);
			memcpy(_data + offset, &senderClientId, sz);
			offset += sz;

			// hasta aqui los no necesarios

			sz = sizeof(MsgId);
			memcpy(_data + offset, &id, sz);
			offset += sz;

			sz = sizeof(uint32_t);
			memcpy(_data + offset, &clientId, sz);
		}

		virtual int from_bin(char * data) override {

			//estos creo que no hacen falta pero los meto por si acaso
			size_t sz = sizeof(ClientDisconnectedMsg);
			memcpy(&size, _data, sz);
			size_t offset = sz;

			sz = sizeof(uint32_t);
			memcpy(&senderClientId, _data + offset, sz);
			offset += sz;

			// hasta aqui los no necesarios

			sz = sizeof(MsgId);
			memcpy(&id, _data + offset, sz);
			offset += sz;

			sz = sizeof(uint32_t);
			memcpy(&clientId, _data + offset, sz);
			return 0;
		}
		uint32_t clientId;
	};

	struct PlayerInfo : Message {
		PlayerInfo(const char* n) :
			Message(sizeof(PlayerInfo), _PLAYER_INFO) {
			strncpy(&name[0], n, 11);
		}
		virtual void to_bin() override {
			//estos creo que no hacen falta pero los meto por si acaso
			size_t sz = sizeof(PlayerInfo);
			memcpy(_data, &size, sz);
			size_t offset = sz;

			sz = sizeof(uint32_t);
			memcpy(_data + offset, &senderClientId, sz);
			offset += sz;

			// hasta aqui los no necesarios

			sz = sizeof(MsgId);
			memcpy(_data + offset, &id, sz);
			offset += sz;

			sz = sizeof(char) * 11;
			memcpy(_data + offset, &name, sz);
		}

		virtual int from_bin(char * data) override {

			//estos creo que no hacen falta pero los meto por si acaso
			size_t sz = sizeof(PlayerInfo);
			memcpy(&size, _data, sz);
			size_t offset = sz;

			sz = sizeof(uint32_t);
			memcpy(&senderClientId, _data + offset, sz);
			offset += sz;

			// hasta aqui los no necesarios

			sz = sizeof(MsgId);
			memcpy(&id, _data + offset, sz);
			offset += sz;

			sz = sizeof(char) * 11;
			memcpy(&name, _data + offset, sz);
			return 0;
		}
		char name[11];
	};

	struct FighterInfo : Message {
		FighterInfo(double x, double y, double rot) :
			Message(sizeof(FighterInfo), _FIGHTER_INFO), x(x), y(y), rot(rot) {

		}
		virtual void to_bin() override {
			//estos creo que no hacen falta pero los meto por si acaso
			size_t sz = sizeof(FighterInfo);
			memcpy(_data, &size, sz);
			size_t offset = sz;

			sz = sizeof(uint32_t);
			memcpy(_data + offset, &senderClientId, sz);
			offset += sz;

			// hasta aqui los no necesarios

			sz = sizeof(MsgId);
			memcpy(_data + offset, &id, sz);
			offset += sz;

			sz = sizeof(double);
			memcpy(_data + offset, &x, sz);
			offset += sz;

			memcpy(_data + offset, &y, sz);
			offset += sz;

			memcpy(_data + offset, &rot, sz);
			offset += sz;
		}

		virtual int from_bin(char * data) override {

			//estos creo que no hacen falta pero los meto por si acaso
			size_t sz = sizeof(FighterInfo);
			memcpy(&size, _data, sz);
			size_t offset = sz;

			sz = sizeof(uint32_t);
			memcpy(&senderClientId, _data + offset, sz);
			offset += sz;

			// hasta aqui los no necesarios

			sz = sizeof(MsgId);
			memcpy(&id, _data + offset, sz);
			offset += sz;

			sz = sizeof(double);
			memcpy(&x, _data + offset, sz);
			offset += sz;

			memcpy(&y, _data + offset, sz);
			offset += sz;

			memcpy(&rot, _data + offset, sz);
			offset += sz;
			return 0;
		}
		double x;
		double y;
		double rot;
	};

	struct BulletInfo : Message {
		BulletInfo(uint8_t bulI, Vector2D p, Vector2D v) : 
		Message(sizeof(BulletInfo), _BULLET_INFO), id(bulI), pos(p), vel(v){

		}
		virtual void to_bin() override {
			//estos creo que no hacen falta pero los meto por si acaso
			size_t sz = sizeof(BulletInfo);
			memcpy(_data, &size, sz);
			size_t offset = sz;

			sz = sizeof(uint32_t);
			memcpy(_data + offset, &senderClientId, sz);
			offset += sz;

			// hasta aqui los no necesarios

			sz = sizeof(MsgId);
			memcpy(_data + offset, &id, sz);
			offset += sz;

			// aqui esta el segundo id
			// sz = sizeof(uint8_t);
			// memcpy(_data + offset, &id, sz);
			// offset += sz;

			sz = sizeof(Vector2D);
			memcpy(_data + offset, &pos, sz);
			offset += sz;

			memcpy(_data + offset, &vel, sz);
		}

		virtual int from_bin(char * data) override {

			//estos creo que no hacen falta pero los meto por si acaso
			size_t sz = sizeof(BulletInfo);
			memcpy(&size, _data, sz);
			size_t offset = sz;

			sz = sizeof(uint32_t);
			memcpy(&senderClientId, _data + offset, sz);
			offset += sz;

			// hasta aqui los no necesarios

			sz = sizeof(MsgId);
			memcpy(&id, _data + offset, sz);
			offset += sz;

			// aqui esta el segundo id
			// sz = sizeof(uint8_t);
			// memcpy(_data + offset, &id, sz);
			// offset += sz;

			sz = sizeof(Vector2D);
			memcpy(&pos, _data + offset, sz);
			offset += sz;

			memcpy(&vel, _data + offset, sz);
		}
		uint8_t id;

		Vector2D pos;
		Vector2D vel;
	};

	struct Shoot : Message {
		Shoot(Vector2D p, Vector2D v, double w, double h) : 
			Message(sizeof(Shoot), _SHOOT), pos(p), vel(v), w(w), h(h) {

		}
		virtual void to_bin() override {
			//estos creo que no hacen falta pero los meto por si acaso
			size_t sz = sizeof(Shoot);
			memcpy(_data, &size, sz);
			size_t offset = sz;

			sz = sizeof(uint32_t);
			memcpy(_data + offset, &senderClientId, sz);
			offset += sz;

			// hasta aqui los no necesarios

			sz = sizeof(MsgId);
			memcpy(_data + offset, &id, sz);
			offset += sz;

			sz = sizeof(Vector2D);
			memcpy(_data + offset, &pos, sz);
			offset += sz;

			memcpy(_data + offset, &vel, sz);
			offset += sz;

			sz = sizeof(double);
			memcpy(_data + offset, &w, sz);
			offset += sz;

			memcpy(_data + offset, &h, sz);
		}

		virtual int from_bin(char * data) override {

			//estos creo que no hacen falta pero los meto por si acaso
			size_t sz = sizeof(Shoot);
			memcpy(&size, _data, sz);
			size_t offset = sz;

			sz = sizeof(uint32_t);
			memcpy(&senderClientId, _data + offset, sz);
			offset += sz;

			// hasta aqui los no necesarios

			sz = sizeof(MsgId);
			memcpy(&id, _data + offset, sz);
			offset += sz;
			
			sz = sizeof(Vector2D);
			memcpy(&pos, _data + offset, sz);
			offset += sz;

			memcpy(&vel, _data + offset, sz);
			offset += sz;

			sz = sizeof(double);
			memcpy(&w, _data + offset, sz);
			offset += sz;

			memcpy(&h, _data + offset, sz);
			return 0;
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
		virtual void to_bin() override {
			//estos creo que no hacen falta pero los meto por si acaso
			size_t sz = sizeof(FighterDeath);
			memcpy(_data, &size, sz);
			size_t offset = sz;

			sz = sizeof(uint32_t);
			memcpy(_data + offset, &senderClientId, sz);
			offset += sz;

			// hasta aqui los no necesarios

			sz = sizeof(MsgId);
			memcpy(_data + offset, &id, sz);
			offset += sz;

			sz = sizeof(Vector2D);
			memcpy(_data + offset, &fighterID, sz);
		}

		virtual int from_bin(char * data) override {

			//estos creo que no hacen falta pero los meto por si acaso
			size_t sz = sizeof(FighterDeath);
			memcpy(&size, _data, sz);
			size_t offset = sz;

			sz = sizeof(uint32_t);
			memcpy(&senderClientId, _data + offset, sz);
			offset += sz;

			// hasta aqui los no necesarios

			sz = sizeof(MsgId);
			memcpy(&id, _data + offset, sz);
			offset += sz;

			sz = sizeof(uint32_t);
			memcpy(&fighterID, _data + offset, sz);
			return 0;
		}
		uint32_t fighterID;
	};

#pragma pack(pop)
}
