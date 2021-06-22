//#include <string>
#include <cstring>
#include <memory>
//#include <unistd.h>

#include "GameMessage.h"

void GameMessage::to_bin()
{
    write_Header(sizeof(GameMessage));
}

void GameMessage::write_Header(size_t size){
    alloc_data(size);

    memset(_data, 0, size);

    //Serializar los campos type, nick y message en el buffer _data

    char* b = _data;

    memcpy(b, &type, sizeof(type));
    b += sizeof(type);

    memcpy(b, &matchId, sizeof(matchId));
    b += sizeof(matchId);

    // memcpy(b, nick.c_str(), sizeof(char) * NICK_SIZE);
    // b += sizeof(char) * NICK_SIZE;

    // memcpy(b, message.c_str(), sizeof(char) * message.length());
    // b += sizeof(char) * MSG_SIZE;
}

int GameMessage::from_bin(char * bobj)
{
    return read_Header(bobj);
}

int GameMessage::read_Header(char * bobj){
    alloc_data(MAX_MESSAGE_SIZE);

    memcpy(static_cast<void *>(_data), bobj, MAX_MESSAGE_SIZE);

    //Reconstruir la clase usando el buffer _data

    char* b = _data;

    int offset = 0;

    memcpy(&type, b, sizeof(type));
    b += sizeof(type);
    offset += sizeof(type);

    memcpy(&matchId, b, sizeof(matchId));
    b += sizeof(matchId);
    offset += sizeof(matchId);

    // nick = std::string(sizeof(char) * NICK_SIZE, '\0');
    // memcpy((void *)nick.c_str(), b, sizeof(char) * NICK_SIZE);
    // b += sizeof(char) * NICK_SIZE;

    // message = std::string(sizeof(char) * MSG_SIZE, '\0');
    // memcpy((void *)message.c_str(), b, sizeof(char) * MSG_SIZE);
    return offset;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

void MSGPlayerInfo::to_bin(){
    write_Header(sizeof(GameMessage) + name.size());
    
    char* b = _data + sizeof(GameMessage);

    memcpy(b, name.c_str(), sizeof(char) * name.size());
    // b += sizeof(char) * NICK_SIZE;
}

int MSGPlayerInfo::from_bin(char * bobj){
    read_Header(bobj);

    char* b = _data + sizeof(GameMessage);

    name = std::string(sizeof(char) * MAX_NAME_LENGTH, '\0');
    memcpy((void *)name.c_str(), b, sizeof(char) * MAX_NAME_LENGTH);
    return 0;
}

void MSGPaddlesInfo::to_bin(){
    write_Header(sizeof(GameMessage) + sizeof(std::pair<float, float>));
    
    char* b = _data + sizeof(GameMessage);

    memcpy(b, &position1_, sizeof(std::pair<float, float>));
    // b += sizeof(char) * NICK_SIZE;
}

int MSGPaddlesInfo::from_bin(char * bobj){
    read_Header(bobj);

    char* b = _data +  + sizeof(std::pair<float, float>);

    memcpy(&position1_, b, sizeof(std::pair<float, float>));

    return 0;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

void MSGSetMatch::to_bin(){
    write_Header(sizeof(MSGSetMatch));
    
    char* b = _data + sizeof(GameMessage);

    memcpy(b, &playerId, sizeof(playerId));
    // b += sizeof(char) * NICK_SIZE;
}

int MSGSetMatch::from_bin(char * bobj){
    read_Header(bobj);

    char* b = _data + sizeof(GameMessage);

    playerId = 0;
    memcpy(&playerId, b, sizeof(playerId));
    return 0;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

void MSGShoot::to_bin(){
    write_Header(sizeof(MSGShoot));
    
    char* b = _data + sizeof(GameMessage);

    memcpy(b, &pos, sizeof(Vector2D));
    b += sizeof(Vector2D);

    memcpy(b, &dir, sizeof(Vector2D));
    b += sizeof(Vector2D);

    memcpy(b, &bulletId, sizeof(size_t));
    //b += sizeof(size_t);
}

int MSGShoot::from_bin(char * bobj){
    read_Header(bobj);

    char* b = _data + sizeof(GameMessage);

    memcpy(&pos, b, sizeof(Vector2D));
    b += sizeof(Vector2D);

    memcpy(&dir, b, sizeof(Vector2D));
    b += sizeof(Vector2D);

    memcpy(&bulletId, b, sizeof(size_t));
    //b += sizeof(size_t);

    return 0;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

void MSGMovePaddle::to_bin(){
    write_Header(sizeof(MSGMovePaddle));
    
    char* b = _data + sizeof(GameMessage);

    memcpy(b, &playerId, sizeof(playerId));
    b += sizeof(playerId);

    memcpy(b, &pos, sizeof(Vector2D));
    //b += sizeof(Vector2D);
}

int MSGMovePaddle::from_bin(char * bobj){
    read_Header(bobj);

    char* b = _data + sizeof(GameMessage);

    memcpy(&playerId, b, sizeof(playerId));
    b += sizeof(playerId);

    memcpy(&pos, b, sizeof(Vector2D));
    //b += sizeof(Vector2D);

    return 0;
}