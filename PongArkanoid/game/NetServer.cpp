#include "NetServer.h"
#include "GameMessage.h"
#include "Logic.h"

#include <thread>

Match::Match(int mId) : matchId(mId){
    l = new Logic();
}

void Match::calculateLogic(){
    while(true){
        l->Update();
    }
}

void Match::run(){

    std::thread t = std::thread(&Match::calculateLogic, this);
}

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
        Socket* client = nullptr;
        
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
                getClientInMatch(client);
                if(clients.size() == 0){
                    std::cout << "Player Connected in match [" << actualMatch-1 << "]\n";
                    //std::cout << "-> Info: " << *(matches[msgInp->matchId].clients[0].get()) << "\n";
                    //std::cout << "-> Info: " << *(matches[msgInp->matchId].clients[1].get()) << "\n";
                }
                else{
                    std::cout << "Player Waiting:\nInfo: " << *client << "\n";
                    GameMessage msg(GameMessage::MessageType::PLAYER_WAIT);
                    socket.send(&msg, *clients.back());
                }

                break;
            }
            case GameMessage::MessageType::LOGOUT: {
                bool found = false;
                int i = 0;

                auto it = matches.find(msgInp->matchId);
                
                if(it != matches.end())
                {
                    for(i = 0; i < 2; i++){
                        if(*(matches[msgInp->matchId].clients[i].get()) == *client){
                            int j = (i + 1) % 2;

                            Socket* s = matches[msgInp->matchId].clients[j].get();

                            std::unique_ptr<Socket> soc(matches[msgInp->matchId].clients[j].get());
                            clients.push_back(std::move(soc));

                            GameMessage msg(GameMessage::MessageType::PLAYER_WAIT);
                            socket.send(&msg, *clients.back());

                            matches[msgInp->matchId].clients[i].release();
                            matches[msgInp->matchId].clients[j].release();
                            it = matches.erase(it);

                            while(clients.size() >= 2 && matches.size() < Match::MAX_MATCHES){
                                Match m(actualMatch);
                                actualMatch++;
                                m.clients[0] = std::move(clients.front());
                                clients.front().release();
                                clients.pop_front();

                                m.clients[1] = std::move(clients.front());
                                clients.front().release();
                                clients.pop_front();

                                matches[m.getMatchId()] = std::move(m);

                                MSGSetMatch msg(0, m.getMatchId());

                                //GameMessage msg(GameMessage::MessageType::SET_MATCH, m.matchId);
                                
                                // debe avisar a su compañero de la partida
                                // que se ha conectado
                                for(int i = 0; i < 2; i++){
                                    socket.send(&msg, *(matches[m.getMatchId()].clients[i].get()));
                                    msg.playerId = i+1;
                                }

                                std::cout << "Match Created!\n";
                            }

                            std::cout << "Player in match [" << msgInp->matchId << "] Disconnected -> Info: " << *client << "\n";
                            std::cout << "Remaining Players: " << clients.size() << "\n";  
                            found = true;
                            break;
                        }
                    }          
                }

                if(!found){
                    auto itC = clients.begin();
                    while(itC != clients.end() && !found){
                        if(*((*itC).get()) == *client){
                            found = true;
                            std::cout << "Player waiting Disconnected -> Info: " << *client << "\n";
                            *(itC)->release();
                            clients.erase(itC);
                            std::cout << "Remaining Players: " << clients.size() << "\n";  
                            break;
                        }
                        else itC++;
                    }
                    if(!found) std::cout << "User not registered logged off\n";
                }
                break;
            }
            case GameMessage::MessageType::PLAYER_INFO:{
                std::cout << "Player Name: " << static_cast<MSGPlayerInfo*>(msgInp)->name << "\n";
                break;
            }
            case GameMessage::MessageType::SHOOT:{
                auto it = matches.find(msgInp->matchId);
                if(it != matches.end())
                {
                    MSGShoot* m = static_cast<MSGShoot*>(msgInp);
                    m->bulletId = matches[msgInp->matchId].getLogic()->getLastBulletId();;
                    for(int i = 0; i < 2; i++){
                        socket.send(m, *(matches[msgInp->matchId].clients[i].get()));
                    }

                    // se crea para la gestion interna de la bala
                    matches[msgInp->matchId].getLogic()->spawnBullet(m->pos, m->dir, m->bulletId);
                }
                break;
            }
            case GameMessage::MessageType::MOVE_PADDLE:{
                auto it = matches.find(msgInp->matchId);
                if(it != matches.end())
                {
                    MSGMovePaddle* m = static_cast<MSGMovePaddle*>(msgInp);
                    for(int i = 0; i < 2; i++){
                        socket.send(m, *(matches[msgInp->matchId].clients[i].get()));
                    }

                    matches[msgInp->matchId].getLogic()->setPaddlePos(m->playerId, m->pos);
                }
                break;
            }
            default: 
                std::cout << "Message Type unknown " << msgInp->type << "\n";
                return;
        }
    }
}

void NetServer::getClientInMatch(Socket* cl){
    std::unique_ptr<Socket> soc(cl);
    clients.push_back(std::move(soc));

    while(clients.size() >= 2 && matches.size() < Match::MAX_MATCHES){
        Match m(actualMatch);
        actualMatch++;

        m.clients[0] = std::move(clients.front());
        clients.front().release();
        clients.pop_front();

        m.clients[1] = std::move(clients.front());
        clients.front().release();
        clients.pop_front();

        matches[m.getMatchId()] = std::move(m);

        MSGSetMatch msg(0, m.getMatchId());

        //GameMessage msg(GameMessage::MessageType::SET_MATCH, m.matchId);
        
        // debe avisar a su compañero de la partida
        // que se ha conectado
        for(int i = 0; i < 2; i++){
            socket.send(&msg, *(matches[m.getMatchId()].clients[i].get()));
            msg.playerId = i+1;
        }

        std::cout << "Match Created!\n";
    }
}