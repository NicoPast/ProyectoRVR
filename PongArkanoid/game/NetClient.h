#pragma once

#include <memory>

#include "Socket.h"

class SDLGame;

namespace std{
    class thread;
}

class NetClient
{
private:

    /**
     * Socket para comunicar con el servidor
     */
    Socket socket;

    /**
     * Nick del usuario
     */
    std::string nick;

    /**
     * Game reference 
     */
    SDLGame* game;

    std::thread* t;

    uint8_t matchId;
public:
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
    NetClient(SDLGame* g, const char * s, const char * p, const char * n);

    /**
     *  Envía el mensaje de login al servidor
     */
    void login();

    /**
     *  Envía el mensaje de logout al servidor
     */
    void logout();

    /**
     *  Envia un mensaje al server
     */
    void send_Message(GameMessage *msg);

    /**
     *  Rutina del thread de Red. Recibe datos de la red y los "renderiza"
     *  en STDOUT
     */
    void net_thread();

    /**
     *  Empieza a ejecutar el bucle del NetClient
     */
    void run();

    /**
     *  Gets Nombre del cliente 
     */
    std::string& getName();

    /**
     *  Get & Set Match en la que se encuentra el cliente
     */
    uint8_t getMatchId();
    void setMatchId(uint8_t mId);
};