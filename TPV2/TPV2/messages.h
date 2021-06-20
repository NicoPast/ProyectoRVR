#pragma once
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>

#include "Vector2D.h"
#include "Serializable.h"

namespace msg {

	constexpr size_t MESSAGE_SIZE = 1024;
	using msgSizeType = uint32_t;

	enum MsgId : uint8_t {
		_CONNECTED = 0, //
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

	#pragma pack(push, 1)
	
	struct Message : public Serializable{
		Message(msgSizeType size, MsgId id) :
				size(size), senderClientId(0), id(id) {
		}
		Message(MsgId id) :
				Message(sizeof(Message), id) {
		}
		Message(){
			
		}
		virtual void to_bin() {
			createHeader(sizeof(Message));
		}

		virtual int from_bin(char * data) {
			readHeader(data, sizeof(Message));
			return 0;
		}

		// crea una cabecera para el mensaje:
		// MsgId: identificador del mensaje
		// tamano del mensaje: en bytes
		// clientId: quien envia el mensaje
		// devuelve el tamano de la cabecera
		int createHeader(uint32_t messageSize)
		{
			alloc_data(MESSAGE_SIZE);
    		memset(_data, 0, MESSAGE_SIZE);

			size_t sz = sizeof(MsgId);
			memcpy(_data, &id, sz);
			size_t offset = sz;

			sz = messageSize;
			memcpy(_data, &size, sz);
			offset += sz;

			sz = sizeof(uint32_t);
			memcpy(_data + offset, &senderClientId, sz);
			offset += sz;

			return offset;
		}

		// lee la cabecera del mensaje y la guarda
		// devuelve el offset
		int readHeader(char* data, uint32_t messageSize)
		{
			alloc_data(MESSAGE_SIZE);
			memcpy(static_cast<void *>(_data), data, MESSAGE_SIZE);

			size_t sz = sizeof(MsgId);
			memcpy(&id, _data, sz);
			size_t offset = sz;

			sz = messageSize;
			memcpy(&size, _data + offset, sz);
			offset += sz;

			sz = sizeof(uint32_t);
			memcpy(&senderClientId, _data + offset, sz);
			offset += sz;
			
			return offset;
		}
		msgSizeType size;			
		uint32_t senderClientId;
		MsgId id;
	};

	struct ConnectedMsg: Message {
		ConnectedMsg(int clientId) :
				Message(sizeof(ConnectedMsg), _CONNECTED), clientId(clientId) {
		}
		virtual void to_bin() override {
			
			size_t offset = createHeader(sizeof(ConnectedMsg));
			size_t sz = sizeof(uint32_t);

			memcpy(_data + offset, &clientId, sz);
		}

		virtual int from_bin(char * data) override {
			
			cout << "TEST FromBin ConnectedMsg\n";
			size_t offset = readHeader(data, sizeof(ConnectedMsg));
			size_t sz = sizeof(uint32_t);
			
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
			
			size_t offset = createHeader(sizeof(ClientDisconnectedMsg));
			size_t sz = sizeof(uint32_t);

			memcpy(_data + offset, &clientId, sz);
		}

		virtual int from_bin(char * data) override {

			size_t offset = readHeader(data, sizeof(ClientDisconnectedMsg));
			size_t sz = sizeof(uint32_t);

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
			
			size_t offset = createHeader(sizeof(PlayerInfo));
			size_t sz = sizeof(char) * 11;

			memcpy(_data + offset, &name, sz);
		}

		virtual int from_bin(char * data) override {

			size_t offset = readHeader(data, sizeof(PlayerInfo));
			size_t sz = sizeof(char) * 11;

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
			size_t offset = createHeader(sizeof(FighterInfo));
			size_t sz = sizeof(double);

			memcpy(_data + offset, &x, sz);
			offset += sz;

			memcpy(_data + offset, &y, sz);
			offset += sz;

			memcpy(_data + offset, &rot, sz);
			offset += sz;
		}

		virtual int from_bin(char * data) override {

			size_t offset = readHeader(data, sizeof(FighterInfo));
			size_t sz = sizeof(double);

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
		Message(sizeof(BulletInfo), _BULLET_INFO), bulletId(bulI), pos(p), vel(v){

		}
		virtual void to_bin() override {
			
			size_t offset = createHeader(sizeof(BulletInfo));
			size_t sz = sizeof(uint8_t);
			
			memcpy(_data + offset, &bulletId, sz);
			offset += sz;

			sz = sizeof(Vector2D);
			memcpy(_data + offset, &pos, sz);
			offset += sz;

			memcpy(_data + offset, &vel, sz);
		}

		virtual int from_bin(char * data) override {

			size_t offset = readHeader(data, sizeof(BulletInfo));
			size_t sz = sizeof(uint8_t);
			memcpy(_data + offset, &id, sz);
			offset += sz;

			sz = sizeof(Vector2D);
			memcpy(&pos, _data + offset, sz);
			offset += sz;

			memcpy(&vel, _data + offset, sz);
			return 0;
		}
		uint8_t bulletId;

		Vector2D pos;
		Vector2D vel;
	};

	struct Shoot : Message {
		Shoot(Vector2D p, Vector2D v, double w, double h) : 
			Message(sizeof(Shoot), _SHOOT), pos(p), vel(v), w(w), h(h) {

		}
		virtual void to_bin() override {

			size_t offset = createHeader(sizeof(Shoot));
			size_t sz = sizeof(Vector2D);

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

			size_t offset = readHeader(data, sizeof(Shoot));
			size_t sz = sizeof(Vector2D);

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
			size_t offset = createHeader(sizeof(FighterDeath));
			size_t sz = sizeof(Vector2D);

			memcpy(_data + offset, &fighterID, sz);
		}

		virtual int from_bin(char * data) override {

			size_t offset = readHeader(data, sizeof(FighterDeath));
			size_t sz = sizeof(uint32_t);

			memcpy(&fighterID, _data + offset, sz);
			return 0;
		}
		uint32_t fighterID;
	};
#pragma pack(pop)
}
