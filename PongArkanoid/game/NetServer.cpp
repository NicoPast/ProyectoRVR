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
                int i = 0;
                bool entered = false;

                // hace matchmaking
                // intenta entrar en la siguiente partida libre
                for(i = 0; i < 2; i++){
                    if(!matches[actualMatch].occupied[i]){
                        std::unique_ptr<Socket> soc(client);
                        matches[actualMatch].clients[i] = std::move(soc);
                        matches[actualMatch].occupied[i] = true;

                        std::cout << "Player Connected:\nInfo: " << *client << "\n";
                        GameMessage msg (GameMessage::MessageType::SET_MATCH, actualMatch);
                        socket.send(&msg, *client);

                        if(i == 1){
                            actualMatch = (actualMatch + 1) % Match::MAX_MATCHES;
                        }
                        entered = true;
                        break;
                    }
                }

                // si no pudo, espera a la siguiente
                if(!entered){
                    std::cout << "Player Waiting:\nInfo: " << *client << "\n";
                    std::unique_ptr<Socket> soc(client);
                    clients.push_back(std::move(soc));
                    full = true;
                }

                // debe avisar a su compañero de la partida
                // que se ha conectado

                // std::string m = msgInp.nick + " logged in.";
                // //std::string m2 = "Connected users: " + std::to_string(clients.size());
                // msgOut.type = ChatMessage::SERVER_MSG;
                // msgOut.nick = "SERV";
                // //msgOut.message = m2;
                // //socket.send(msgOut, *client);
                // msgOut.message = m;
                //std::cout << "Player Connected:\nInfo: " << *client << "\n";
                break;
            }
            case GameMessage::MessageType::LOGOUT: {
                auto it = clients.begin();
                bool found = false;
                int i = 0;
                for(i = 0; i < 2; i++){
                    Socket* s = matches[msgInp->matchId].clients[i].get();
                    if(*s == *client){
                        matches[msgInp->matchId].clients[i].release();
                        matches[msgInp->matchId].occupied[i] = false;
                        break;
                    }
                    std::cout << matches[msgInp->matchId].occupied[i] << "\n";
                }
                // while(it != clients.end() && !found){
                //     if(*((*it).get()) == *client){
                //         found = true;
                //     }
                //     else it++;
                // }
                
                if(i < 2){
                    // std::string m = msgInp.nick + " logged out.";
                    //clients.erase(it);
                    // msgOut.type = ChatMessage::SERVER_MSG;
                    // msgOut.nick = "Server";
                    // msgOut.message = m;
                    std::cout << "Player Disconnected:\nInfo: " << *client << "\n";
                    std::cout << "Remaining Players: " << clients.size() << "\n";
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
    }
}