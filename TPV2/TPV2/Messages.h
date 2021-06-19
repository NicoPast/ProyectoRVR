#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <memory>

#include "Serializable.h"
#include "Socket.h"
#include "BulletInfo.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
 *  Clase mensaje general, de la que heredan el resto de mensajes para tener una estructura general compartida
 * 
 *  +--------------------+
 *  | Tipo: uint8_t      | 0 (login), 1 (mensaje), 2 (logout)
 *  +--------------------+
 *  |                    |
 *  |      Mensaje:      | Mensaje con la info que se quiera enviar (salvo en el caso de que el tipo sea LOGOUT)
 *  |                    | Tamano maximo permitido: Socket::MAX_MESSAGE_SIZE (de momento 1KB)
 *  +--------------------+
 *
 */
class Message: public Serializable
{
    public:
    static const size_t MESSAGE_SIZE = sizeof(char) * 1024 + sizeof(uint8_t);

    enum MessageType
    {
        LOGIN   = 0,
        MESSAGE = 1,
        LOGOUT  = 2
    };

    Message(){};

    virtual void to_bin() {};

    virtual int from_bin(char * bobj) {};

    uint8_t type;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

/**
 *  Mensaje del servidor al cliente para enviar el mapa entero. Se envia muy de vez en cuando
 *
 *  +----------------------------------+
 *  | Tipo                             | Tiene que ser 1 (message)
 *  +----------------------------------+
 *  | Tamano: <int,int>                | Tamano de la pared de bloques
 *  +----------------------------------+
 *  |                                  |
 *  | Bloques: [bool][bool]            | true significa que en esa posicion hay bloque; false, que no lo hay
 *  |                                  |
 *  +----------------------------------+
 *
 */
class MapMessage: public Message
{
public:

    MapMessage(){};

    MapMessage(std::pair<float, float> pos){};

    void to_bin();

    int from_bin(char * bobj);

    std::pair<int, int> size;
    //bool blocks[][];
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
 *  Mensaje del servidor al cliente para informar de la posicion y demas info
 *
 *  +-------------------+
 *  | Tipo              | Tiene que ser 1 (message)
 *  +-------------------+
 *  | Posicion server   | Para ajustar la posicion del jugador servidor
 *  +-------------------+
 *  | Direccion server  | Para que se vaya moviendo hasta que llegue el siguiente mensaje
 *  +-------------------+
 *  | Numero de  balas  | Numero de balas que hay ahora mismo en el campo
 *  +-------------------+
 *  |                   |
 *  | Balas: []         | Todas las balas que hay en el juego: info de la posicion y direccion de cada una
 *  |                   |
 *  +-------------------+
 *
 */
class UpdateMessage: public Message
{
public:
    static const size_t MESSAGE_SIZE = sizeof(char) * 88 + sizeof(uint8_t);

    UpdateMessage(){};

    void to_bin();

    int from_bin(char * bobj);

    uint8_t type;
    Vector2D position;
    Vector2D direction;
    int bulletsNum;
    BulletInfo bullets[];
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

/**
 *  Clase para el servidor de chat
 */
class ChatServer
{
public:
    ChatServer(const char * s, const char * p): socket(s, p)
    {
        socket.bind();
    };

    /**
     *  Thread principal del servidor recive mensajes en el socket y
     *  lo distribuye a los clientes. Mantiene actualizada la lista de clientes
     */
    void do_messages();

private:
    /**
     *  Lista de clientes conectados al servidor de Chat, representados por
     *  su socket
     */
    std::vector<std::unique_ptr<Socket>> clients;

    /**
     * Socket del servidor
     */
    Socket socket;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

/**
 *  Clase para el cliente de chat
 */
class ChatClient
{
public:
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     */
    ChatClient(const char * s, const char * p):socket(s, p){};

    /**
     *  Envía el mensaje de login al servidor
     */
    void login();

    /**
     *  Envía el mensaje de logout al servidor
     */
    void logout();

    // creo que no hace falta porque se envia un mensaje cuando se pulsa alguna tecla relevante (?)
    /**
     *  Rutina principal para el Thread de E/S. Lee datos de STDIN (std::getline)
     *  y los envía por red vía el Socket.
     */
    //void input_thread();

    /**
     *  Rutina del thread de Red. Recibe datos de la red y los "renderiza"
     *  en STDOUT
     */
    void net_thread();

private:

    /**
     * Socket para comunicar con el servidor
     */
    Socket socket;
};