#include "SDLGame.h"
#include "GameMessage.h"
#include "NetClient.h"
#include <thread>

NetClient::NetClient(SDLGame* g, const char * s, const char * p, const char * n):
        game(g),
        socket(s, p),
        nick(n){
};

void NetClient::login()
{
    GameMessage msg(GameMessage::MessageType::LOGIN, matchId);

    socket.send(&msg, socket);
}

void NetClient::logout()
{
    GameMessage msg(GameMessage::MessageType::LOGOUT, matchId);

    socket.send(&msg, socket);
}

void NetClient::send_Message(GameMessage *msg)
{
    socket.send(msg, socket);
}

void NetClient::net_thread()
{
    while(true)
    {
        //Recibir Mensajes de red
        Socket* s;
        GameMessage* msgInp = socket.recv(s);

        if(msgInp == nullptr){
            continue;
        }

        game->manageMsg(msgInp);
    }
}

void NetClient::run(){
    t = new std::thread(&NetClient::net_thread, this);

    login();
}

std::string& NetClient::getName(){
    return nick;
}

uint8_t NetClient::getMatchId(){
    return matchId;
}