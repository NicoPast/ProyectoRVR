#include <string.h>

#include "Serializable.h"
#include "Socket.h"
#include "GameMessage.h"

Socket::Socket(const char * address, const char * port):sd(-1)
{
    //Construir un socket de tipo AF_INET y SOCK_DGRAM usando getaddrinfo.
    //Con el resultado inicializar los miembros sd, sa y sa_len de la clase
    struct addrinfo hints;
    struct addrinfo *res;

    memset((void *)&hints, 0, sizeof(addrinfo));

    // permite filtrar las direcciones
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    int ret = getaddrinfo(address, port, &hints, &res);

    if (ret != 0)
    {
        std::cerr << "Error: IP or port not known -> " << address << ":" << port << "\n";
        return;
    }

    sd = socket(res->ai_family, res->ai_socktype, 0);

    if (sd == -1)
    {
        std::cerr << "Error creating the socket: " << errno << std::endl;
        freeaddrinfo(res);
        return;
    }

    sa = *((struct sockaddr*)res->ai_addr);
    sa_len = res->ai_addrlen;
}

GameMessage* Socket::recv(Socket * &sock)
{
    struct sockaddr sa;
    socklen_t sa_len = sizeof(struct sockaddr);

    GameMessage* obj;

    GameMessage msg;

    char buffer[MAX_MESSAGE_SIZE];

    ssize_t bytes = ::recvfrom(sd, buffer, MAX_MESSAGE_SIZE, 0, &sa, &sa_len);

    if ( bytes <= 0 )
    {
        return nullptr;
    }

    if ( sock == nullptr)
    {
        sock = new Socket(&sa, sa_len);
    }

    msg.from_bin(buffer);

    switch (msg.type)
    {
    case GameMessage::MessageType::PLAYER_INFO:
        obj = new MSGPlayerInfo();
        static_cast<MSGPlayerInfo*>(obj)->from_bin(buffer);
        break;
    case GameMessage::MessageType::SERVER_MSG:
        obj = new MSGServerMsg();
        static_cast<MSGServerMsg*>(obj)->from_bin(buffer);
        break;
    case GameMessage::MessageType::SET_MATCH:
        obj = new MSGSetMatch();
        static_cast<MSGSetMatch*>(obj)->from_bin(buffer);
        break;
    case GameMessage::MessageType::END:
        obj = new MSGEndRound();
        static_cast<MSGEndRound*>(obj)->from_bin(buffer);
        break;
    case GameMessage::MessageType::SHOOT:
        obj = new MSGShoot();
        static_cast<MSGShoot*>(obj)->from_bin(buffer);
        break;
    case GameMessage::MessageType::MOVE_PADDLE:
        obj = new MSGMovePaddle();
        static_cast<MSGMovePaddle*>(obj)->from_bin(buffer);
        break;
    case GameMessage::MessageType::UPDATE_BULLET:{
        obj == new MSGUpdateBullet();
        static_cast<MSGUpdateBullet*>(obj)->from_bin(buffer);
        break;
    }
    case GameMessage::MessageType::PLAYER_WAIT:
    default:
        obj = new GameMessage();
        obj->from_bin(buffer);
        break;
    }
    return obj;
}

int Socket::send(Serializable* obj, const Socket& sock)
{
    //Serializar el objeto
    obj->to_bin();
    //Enviar el objeto binario a sock usando el socket sd
    return sendto(sd, obj->data(), obj->size(), 0, &sock.sa, sock.sa_len);
}

bool operator== (const Socket &s1, const Socket &s2)
{
    //Comparar los campos sin_family, sin_addr.s_addr y sin_port
    //de la estructura sockaddr_in de los Sockets s1 y s2
    //Retornar false si alguno difiere
    sockaddr_in so1 = (const sockaddr_in&)(s1.sa);
    sockaddr_in so2 = (const sockaddr_in&)(s2.sa);
    return
           so1.sin_addr.s_addr   == so2.sin_addr.s_addr &&
           so1.sin_family        == so2.sin_family      &&
           so1.sin_port          == so2.sin_port;
};

std::ostream& operator<<(std::ostream& os, const Socket& s)
{
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    getnameinfo((struct sockaddr *) &(s.sa), s.sa_len, host, NI_MAXHOST, serv,
                NI_MAXSERV, NI_NUMERICHOST);

    os << host << ":" << serv;

    return os;
};

