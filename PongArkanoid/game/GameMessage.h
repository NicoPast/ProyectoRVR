#pragma once

#include <string>

#include "Serializable.h"
#include "Vector2D.h"

/**
 *  Mensaje del protocolo de la aplicación de Chat
 *
 *  +-------------------+
 *  | Tipo: uint8_t     | 0 (login), 1 (logout), ...
 *  +-------------------+
 *  | Tipo: int         | match_id -> id de la partida actual
 *  +-------------------+
 *
 */
struct GameMessage: public Serializable
{
    static const size_t NICK_SIZE = 8; 
    static const size_t MSG_SIZE = 80; 
    static const size_t MAX_NAME_LENGTH = 16;
    static const size_t MAX_SERVER_MSG_LENGTH = 256;
    static const size_t MAX_MESSAGE_SIZE = 1024;

    enum MessageType
    {
        LOGIN = 0,
        LOGOUT,
        SERVER_MSG,   // uso mensajes genericos
        SET_MATCH,
        PLAYER_WAIT,
        PLAYER_INFO,
        MOVE_PADDLE,
        UPDATE_PLAYER,
        SHOOT,
        UPDATE_BULLET,
        END,

        lastMsg
    };

    GameMessage(){};

    GameMessage(MessageType msgT, int mId) : type(msgT), matchId(mId){};

    GameMessage(MessageType msgT) : type(msgT){};

    void to_bin();

    int from_bin(char * bobj);

    void write_Header(size_t size);

    int read_Header(char * bobj);

    uint8_t type = SERVER_MSG;

    int matchId = -1;
};

struct MSGPlayerInfo : public GameMessage{
    MSGPlayerInfo() : GameMessage(PLAYER_INFO, 0){}

    MSGPlayerInfo(std::string n, int matchId) : 
    GameMessage(PLAYER_INFO, matchId), name(n) {
        if(name.size() > MAX_NAME_LENGTH)
            name.resize(MAX_NAME_LENGTH);
    }

    void to_bin();

    int from_bin(char * bobj);

    std::string name;
};

struct MSGSetMatch : public GameMessage{
    MSGSetMatch() : GameMessage(SET_MATCH, 0){}

    MSGSetMatch(int n, int matchId) : 
    GameMessage(SET_MATCH, matchId), playerId(n) {
        
    }

    void to_bin();

    int from_bin(char * bobj);

    int playerId;
};

struct MSGEndRound : public GameMessage{
    MSGEndRound() : GameMessage(END, 0){}

    MSGEndRound(int n, int matchId) : 
    GameMessage(END, matchId), playerId(n) {
        
    }

    void to_bin();

    int from_bin(char * bobj);

    int playerId;
};

struct MSGServerMsg : public GameMessage{
    MSGServerMsg() : GameMessage(SERVER_MSG, 0){}

    MSGServerMsg(std::string n, int matchId) : 
    GameMessage(SERVER_MSG, matchId), name(n) {
        if(name.size() > MAX_NAME_LENGTH)
            name.resize(MAX_NAME_LENGTH);
    }

    void to_bin();

    int from_bin(char * bobj);

    std::string name;
};

struct MSGPaddlesInfo : public GameMessage{
    MSGPaddlesInfo() : GameMessage(UPDATE_PLAYER, 0){}

    MSGPaddlesInfo(Vector2D player1, Vector2D player2, int matchId) : 
    GameMessage(UPDATE_PLAYER, matchId), position1_(player1), position2_(player2) {

    }

    void to_bin();

    int from_bin(char * bobj);

    Vector2D position1_;
    Vector2D position2_;
};

struct MSGMovePaddle : public GameMessage{
    MSGMovePaddle() : GameMessage(MOVE_PADDLE, 0) {}

    MSGMovePaddle(Vector2D p, uint8_t id, int matchId) : 
    GameMessage(MOVE_PADDLE, matchId), pos(p), playerId(id) {

    }

    void to_bin();

    int from_bin(char * bobj);

    uint8_t playerId;

    Vector2D pos;
};

struct MSGShoot : public GameMessage {
    MSGShoot() : GameMessage(SHOOT, 0) {}

    MSGShoot(Vector2D p, Vector2D d, size_t id, int b, int matchId) : 
    GameMessage(SHOOT, matchId), pos(p), dir(d), bounces(b), bulletId(id) {}

    void to_bin();

    int from_bin(char * bobj);

    Vector2D pos;
    Vector2D dir;

    size_t bulletId;

    int bounces;
};

struct MSGUpdateBullet : public GameMessage {
    MSGUpdateBullet() : GameMessage(UPDATE_BULLET, 0) {}

    MSGUpdateBullet(Vector2D p, Vector2D d, size_t id, int b, int matchId) : 
    GameMessage(UPDATE_BULLET, matchId), pos(p), dir(d), bulletId(id), bounces(b) {}

    void to_bin();

    int from_bin(char * bobj);

    Vector2D pos;
    Vector2D dir;

    size_t bulletId;

    int bounces;
};