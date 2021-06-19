#include "Messages.h"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void UpdateMessage::to_bin()
{
    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);

    size_t offset = 0, size = sizeof(type);
    memcpy(_data, &type, size);
    offset += size;
    
    size = sizeof(Vector2D);
    memcpy(_data + offset, &position, size);
    offset += size;

    memcpy(_data + offset, &direction, size);
    offset += size;

    size = sizeof(int);
    memcpy(_data + offset, &bulletsNum, size);
    offset += size;

    size = sizeof(BulletInfo) * bulletsNum;
    memcpy(_data + offset, &bullets, size);
}

int UpdateMessage::from_bin(char * bobj)
{
    alloc_data(MESSAGE_SIZE);

    memcpy(static_cast<void *>(_data), bobj, MESSAGE_SIZE);

    size_t offset = 0, size = sizeof(type);
    memcpy(&type, bobj + offset, size);
    offset += size;
    
    size = sizeof(Vector2D);
    memcpy(&position, _data + offset, size);
    offset += size;

    memcpy(&direction, _data + offset, size);
    offset += size;

    size = sizeof(int);
    memcpy(&bulletsNum, &_data + offset, size);
    offset += size;

    size = sizeof(BulletInfo) * bulletsNum;
    memcpy(&bullets, _data + offset, size);
    
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void MapMessage::to_bin()
{
    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);

    size_t offset = 0, sz = sizeof(type);
    memcpy(_data, &type, sz);
    offset += sz;

    sz = sizeof(std::pair<int, int>);
    memcpy(_data + offset, &size, sz);
    offset += sz;

    // sz = size.first * size.second * sizeof(bool);
    // memcpy(_data + offset, &blocks, sz);
}

int MapMessage::from_bin(char * bobj)
{
    alloc_data(MESSAGE_SIZE);

    memcpy(static_cast<void *>(_data), bobj, MESSAGE_SIZE);

    //Reconstruir la clase usando el buffer _data
    size_t offset = 0, size = sizeof(type);
    memcpy(&type, bobj + offset, size);
    offset += size;
    
    // sz = size.first * size.second * sizeof(bool);
    // memcpy(&blocks, _data + offset, sz);
    
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void ChatServer::do_messages()
{
    while (true)
    {
        /*
         * NOTA: los clientes están definidos con "smart pointers", es necesario
         * crear un unique_ptr con el objeto socket recibido y usar std::move
         * para añadirlo al vector
         */

        Message message;
        Socket* client;

        socket.recv(message, client);
        std::unique_ptr<Socket> cl(client);

        //Recibir Mensajes en y en función del tipo de mensaje
        // - LOGIN: Añadir al vector clients
        // - LOGOUT: Eliminar del vector clients
        // - MESSAGE: Reenviar el mensaje a todos los clientes (menos el emisor)
        switch (message.type)
        {
        case Message::MessageType::LOGIN:
        {
            // anadimos el cliente
            clients.push_back(std::move(cl));
            break;
        }
        case Message::MessageType::LOGOUT:
        {
            int i = 0;
            bool found = false;

            // buscamos el cliente
            while(i < clients.size() && !found)
            {
                found = clients.at(i) == cl;
                i++;
            }

            // eliminamos el cliente
            if(found)
            {
                clients.erase(clients.begin() + i -1);
            }
            break;
        }
        case Message::MessageType::MESSAGE:
        {
            for(int i = 0; i < clients.size(); i++)
            {
                if(clients.at(i) != cl)
                {
                    socket.send(message, *clients.at(i));
                }
            }
            break;
        }
        default:
            break;
        }
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void ChatClient::login()
{
    Message em;
    em.type = Message::LOGIN;

    socket.send(em, socket);
}

void ChatClient::logout()
{
    Message out;
    out.type = Message::LOGOUT;

    socket.send(out, socket);
}

// void ChatClient::input_thread()
// {
//     // bool exit = false;
//     // while (!exit)
//     // {
//     //     // Leer stdin con std::getline
//     //     // Enviar al servidor usando socket
//     //     Message message;
//     //     std::string msg;
//     //     std::getline(std::cin, msg);

//     //     message.type = Message::MESSAGE;
//     //     message.message = msg;

//     //     // si el usuario quiere salir, mandamos el mensaje de logout
//     //     if(msg == "!exit")
//     //     {
//     //         logout();
//     //         exit = true;
//     //     }
//     //     // si no, enviamos un mensaje con los datos correctos
//     //     else
//     //     {
//     //         socket.send(message, socket);
//     //     }
//     // }
// }

void ChatClient::net_thread()
{
    while(true)
    {
        //Recibir Mensajes de red
        Message message;
        socket.recv(message);
    }
}