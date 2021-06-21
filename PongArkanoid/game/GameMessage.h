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
        PLAYER_INFO,
        UPDATE_PLAYER,
        SHOOT,
        UPDATE_BALL,
        END,

        lastMsg
    };

    GameMessage(){};

    GameMessage(MessageType msgT) : type(msgT){};

    void to_bin();

    int from_bin(char * bobj);

    void write_Header(size_t size);

    int read_Header(char * bobj);

    uint8_t type;
};


struct MSGPlayerInfo : public GameMessage{
    MSGPlayerInfo() : GameMessage(PLAYER_INFO){}

    MSGPlayerInfo(std::string n) : 
    GameMessage(PLAYER_INFO), name(n) {

    }

    void to_bin();

    int from_bin(char * bobj);

    std::string name;
};

struct MSGServerMsg : public GameMessage{

};