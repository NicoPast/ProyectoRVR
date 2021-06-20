#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include <iostream>
#include <stdexcept>

#include <ostream>

// -----------------------------------------------------------------------------
// Definiciones adelantadas
// -----------------------------------------------------------------------------
class Socket;
class Serializable;

/**
 *  Esta función compara dos Socks, realizando la comparación de las structuras
 *  sockaddr: familia (INET), dirección y puerto, ver ip(7) para comparar
 *  estructuras sockaddr_in. Deben comparar el tipo (sin_family), dirección
 *  (sin_addr.s_addr) y puerto (sin_port). La comparación de los campos puede
 *  realizarse con el operador == de los tipos básicos asociados.
 */
bool operator== (const Socket &s1, const Socket &s2);

/**
 *  Imprime la dirección y puerto en número con el formato:"dirección_ip:puerto"
 */
std::ostream& operator<<(std::ostream& os, const Socket& dt);
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


/**
 * Clase base que representa el extremo local de una conexión UDP. Tiene la lógica
 * para inicializar un sockect y la descripción binaria del extremo
 *   - dirección IP
 *   - puerto
 */
class Socket
{
public:
    /**
     * El máximo teórico de un mensaje UDP es 2^16, del que hay que
     * descontar la cabecera UDP e IP (con las posibles opciones). Se debe
     * utilizar esta constante para definir buffers de recepción.
     */
    static const int32_t MAX_MESSAGE_SIZE = 32768;

    /**
     *  Construye el socket UDP con la dirección y puerto dados. Esta función
     *  usara getaddrinfo para obtener la representación binaria de dirección y
     *  puerto.
     *
     *  Además abrirá el canal de comunicación con la llamada socket(2).
     *
     *    @param address cadena que representa la dirección o nombre
     *    @param port cadena que representa el puerto o nombre del servicio
     */
    Socket(const char * address, const char * port):sd(-1)
    {
        //Construir un socket de tipo AF_INET y SOCK_DGRAM usando getaddrinfo.
        //Con el resultado inicializar los miembros sd, sa y sa_len de la clase
        addrinfo hints;
        addrinfo* results;

        memset(&hints, 0, sizeof(struct addrinfo));

        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_flags = AI_PASSIVE;

        int rc = getaddrinfo(address, port, &hints, &results);

        // rc guarda el codigo de error (si hay alguno)
        if(rc != 0)
        {
            printf("Error: %s\n", gai_strerror(rc));
        }
        
        // intentamos crear el socket
        sd = socket(results->ai_family, results->ai_socktype, 0);
        if(sd == -1)
        {
            printf("Error con la creacion de sockets\n");
        }

        // guardamos los miembros sa y sa_len
        sa = *results->ai_addr;
        sa_len = results->ai_addrlen;
    }

    /**
     *  Inicializa un Socket copiando los parámetros del socket
     */
    Socket(struct sockaddr * _sa, socklen_t _sa_len):sd(-1), sa(*_sa),
        sa_len(_sa_len){};

    virtual ~Socket(){};

    /**
     *  Recibe un mensaje de aplicación
     *
     *    @param obj que recibirá los datos de la red. Se usará para la
     *    reconstrucción del objeto mediante Serializable::from_bin del interfaz.
     *
     *    @param sock que identificará al extremo que envía los datos si es
     *    distinto de 0 se creará un objeto Socket con la dirección y puerto.
     *
     *    @return 0 en caso de éxito o -1 si error (cerrar conexión)
     */
    int recv(msg::Message * &obj, Socket * &sock) {
        struct sockaddr sa;
        socklen_t sa_len = sizeof(struct sockaddr);

        char buffer[MAX_MESSAGE_SIZE];

        printf("TEST Before recvfrom\n");

        ssize_t bytes = ::recvfrom(sd, buffer, MAX_MESSAGE_SIZE, 0, &sa, &sa_len);

        printf("TEST After recvfrom\n");

        if ( bytes <= 0 )
        {
            return -1;
        }

        printf("TEST -1?\n");

        if ( sock != nullptr )
        {
            printf("TEST new?\n");
            sock = new Socket(&sa, sa_len);
            printf("TEST !=0?\n");
        }

        printf("TEST from_Bin\n");
        // leer el id del buffer
        // en funcion de que id es, construye ese mensaje
        // switch (expression)
        // {
        // case /* constant-expression */:
        //     /* code */
        //     // obj = new ...;
        //     break;
        
        // default:
        //     break;
        // }

        obj->from_bin(buffer);

        printf("TEST After From_bin\n");

        return 0;
    }

    int recv(msg::Message* &obj) //Descarta los datos del otro extremo
    {
        Socket * s = nullptr;

        return recv(obj, s);
    }

    /**
     *  Envía un mensaje de aplicación definido por un objeto Serializable.
     *
     *    @param obj en el que se enviará por la red. La función lo serializará
     *
     *    @param sock con la dirección y puerto destino
     *
     *    @return 0 en caso de éxito o -1 si error
     */
    int send(Serializable& obj, const Socket& sock)
    {
        //Serializar el objeto
        //Enviar el objeto binario a sock usando el socket sd

        obj.to_bin();
        std::cout << sock.sa_len << "\n";

        int bytes = sendto(sock.sd, obj.data(), obj.size(), 0, &sock.sa, sock.sa_len);

        if(bytes == -1)
        {
            printf("Error al enviar el paquete\n");
            fprintf(stderr, "Error using getaddrinfo: %s\n", gai_strerror(bytes));
        }
        return bytes;
    }

    /**
     *  Enlaza el descriptor del socket a la dirección y puerto
     */
    int bind()
    {
        return ::bind(sd, (const struct sockaddr *) &sa, sa_len);
    }

    friend std::ostream& operator<<(std::ostream& os, const Socket& dt);

    friend bool operator== (const Socket &s1, const Socket &s2);

protected:

    /**
     *  Descriptor del socket
     */
    int sd;

    /**
     *  Representación binaria del extremo, usada por servidor y cliente
     */
    struct sockaddr sa;
    socklen_t       sa_len;
};

#endif /* SOCKET_H_ */