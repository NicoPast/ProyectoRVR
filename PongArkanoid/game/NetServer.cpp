#include "NetServer.h"
#include "GameMessage.h"

void NetServer::do_messages()
{
    GameMessage* msgOut = new GameMessage();

    while (true)
    {
        /*
         * NOTA: los clientes están definidos con "smart pointers", es necesario
         * crear un unique_ptr con el objeto socket recibido y usar std::move
         * para añadirlo al vector
         */
        Socket* client;
        
        GameMessage* msgInp = socket.recv(client);

        if(msgInp == nullptr){
            continue;
        }

        //Recibir Mensajes en y en función del tipo de mensaje
        // - LOGIN: Añadir al vector clients
        // - LOGOUT: Eliminar del vector clients
        // - MESSAGE: Reenviar el mensaje a todos los clientes (menos el emisor)
        switch (msgInp->type)
        {
            case GameMessage::MessageType::LOGIN: {
                std::unique_ptr<Socket> soc(client);
                clients.push_back(std::move(soc));

                // std::string m = msgInp.nick + " logged in.";
                // //std::string m2 = "Connected users: " + std::to_string(clients.size());
                // msgOut.type = ChatMessage::SERVER_MSG;
                // msgOut.nick = "SERV";
                // //msgOut.message = m2;
                // //socket.send(msgOut, *client);
                // msgOut.message = m;
                std::cout << "Player Connected:\nInfo: " << *client << "\n";
                break;
            }
            case GameMessage::MessageType::LOGOUT: {
                auto it = clients.begin();
                bool found = false;
                while(it != clients.end() && !found){
                    if(*((*it).get()) == *client){
                        found = true;
                    }
                    else it++;
                }
                
                if(it != clients.end()){
                    // std::string m = msgInp.nick + " logged out.";
                    // clients.erase(it);
                    // msgOut.type = ChatMessage::SERVER_MSG;
                    // msgOut.nick = "Server";
                    // msgOut.message = m;
                    //std::cout << m << "\n";
                }
                else std::cout << "User not registered logged off\n";
                break;
            }
            case GameMessage::MessageType::PLAYER_INFO:
                std::cout << "Player Name: " << static_cast<MSGPlayerInfo*>(msgInp)->name << "\n";
                break;
            default: 
                std::cout << "Message Type unknown " << msgInp->type << "\n";
                return;
        }

        //std::cout << "Connected users:\n";
        auto it = clients.begin();
        while(it != clients.end()) {
            // std::cout << *((*it).get()) << "\n";
            if(*((*it).get()) == *client){
                it++;
                continue;
            }
            socket.send(msgOut, *((*it).get()));
            it++;
        }
    }
}