#pragma once

#include <string>

#include "Serializable.h"

/**
 *  Mensaje del protocolo de la aplicación de Chat
 *
 *  +-------------------+
 *  | Tipo: uint8_t     | 0 (login), 1 (logout), ...
 *  +-------------------+
 *
 */
struct GameMessage: public Serializable
{
    static const size_t NICK_SIZE = 8; 
    static const size_t MSG_SIZE = 80; 
    static const size_t MAX_NAME_LENGTH = 16;
    static const size_t MAX_MESSAGE_SIZE = 1024;

    enum MessageType
    {
        LOGIN = 0,
        LOGOUT,
        SERVER_MSG,   // uso mensajes genericos
        SET_MATCH,
        PLAYER_WAIT,
        PLAYER_INFO,
        UPDATE_PLAYER,
        SHOOT,
        UPDATE_BALL,
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

    MSGPlayerInfo(std::string n, uint8_t matchId) : 
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

    MSGSetMatch(int n, uint8_t matchId) : 
    GameMessage(SET_MATCH, matchId), playerId(n) {
        
    }

    void to_bin();

    int from_bin(char * bobj);

    int playerId;
};

struct MSGServerMsg : public GameMessage{

};

struct MSGPaddlesInfo : public GameMessage{
    MSGPaddlesInfo(uint8_t matchId) : GameMessage(UPDATE_PLAYER, matchId){}

    MSGPaddlesInfo(std::pair<float, float> player1, uint8_t matchId) : 
    GameMessage(UPDATE_PLAYER, matchId), position1_(player1) {

    }

    void to_bin();

    int from_bin(char * bobj);

    std::pair<float, float> position1_;
};