#pragma once

#include <vector>
#include <list>
#include <map>
#include <memory>
#include <thread>

#include "Socket.h"
#include "Logic.h"

class Match
{
private:

    int matchId;

    std::thread t;

public:
    static const size_t MAX_MATCHES = 1;

    std::unique_ptr<Socket> clients[2];

    Socket* server;
    
    Match();

    Match(int mId, Socket* s);

    // ~Match();

    void run();

    void init();
    
    Logic l;

    void calculateLogic();

    int getMatchId(){
        return matchId;
    }

    Logic* getLogic(){
        return &l;
    }
};

class NetServer{
private:

    /**
     *  Lista de clientes conectados al servidor de juego, representados por
     *  su socket, esperando a entrar en partida
     */
    std::list<std::unique_ptr<Socket>> clients;

    std::map<int, Match> matches;

    int actualMatch = 0;

    bool full = false;

    /**
     * Socket del servidor
     */
    Socket socket;
public:
    NetServer(const char * s, const char * p): socket(s, p)
    {
        socket.bind();
    };

    /**
     *  Thread principal del servidor recive mensajes en el socket y
     *  lo distribuye a los clientes. Mantiene actualizada la lista de clientes
     */
    void do_messages();

    /**
     * Mete a un cliente en la partida que pueda y crea una partida si puede
     * con los que esten esperando
     */
    void getClientInMatch(Socket* cl);
};