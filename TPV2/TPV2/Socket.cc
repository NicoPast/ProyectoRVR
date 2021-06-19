#include "Socket.h"
#include <string.h>
#include "Serializable.h"

int Socket::recv(Serializable &obj, Socket * &sock)
{
    struct sockaddr sa;
    socklen_t sa_len = sizeof(struct sockaddr);

    char buffer[MAX_MESSAGE_SIZE];

    ssize_t bytes = ::recvfrom(sd, buffer, MAX_MESSAGE_SIZE, 0, &sa, &sa_len);

    if ( bytes <= 0 )
    {
        return -1;
    }

    if ( sock != 0 )
    {
        sock = new Socket(&sa, sa_len);
    }

    obj.from_bin(buffer);

    return 0;
}

int Socket::send(Serializable& obj, const Socket& sock)
{
    //Serializar el objeto
    //Enviar el objeto binario a sock usando el socket sd

    obj.to_bin();
    int bytes = sendto(sock.sd, obj.data(), obj.size(), 0, &sock.sa, sock.sa_len);

    if(bytes == -1)
    {
        printf("Error al enviar el paquete\n");
    }
    return bytes;
}

bool operator== (const Socket &s1, const Socket &s2)
{
    //Comparar los campos sin_family, sin_addr.s_addr y sin_port
    //de la estructura sockaddr_in de los Sockets s1 y s2
    //Retornar false si alguno difiere

    sockaddr_in* addr1 = (sockaddr_in*)&s1.sa;
    sockaddr_in* addr2 = (sockaddr_in*)&s2.sa;
    
    return  addr1->sin_family == addr2->sin_family &&
            addr1->sin_addr.s_addr == addr2->sin_addr.s_addr &&
            addr1->sin_port == addr2->sin_port;
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