#pragma once

#include <vector>
#include <memory>

#include "Socket.h"

struct Match
{
    std::unique_ptr<Socket> clients[2];
    bool occupied [2];

    int gameId;
    bool active;
};

class NetServer{
private:
    /**
     *  Lista de clientes conectados al servidor de juego, representados por
     *  su socket, esperando a entrar en partida
     */
    std::vector<std::unique_ptr<Socket>> clients;
    // TO DO: hacer que sean parejas de jugadores y multithreads

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
};