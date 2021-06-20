#include "Networking.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <memory>
#include <thread>

#include "Socket.h"

Networking::Networking() :
		sock(nullptr), //
		socketSet(nullptr), //
		socket(nullptr) //
{
	if (SDLNet_Init() < 0) {
		error();
	}

}

Networking::~Networking() {
	SDLNet_Quit();
	if(socket)
		delete socket;
}

void Networking::send(msg::Message &msg, Socket* sock){
	if(socket->send(msg, *sock) < 0){
		error();
	}
}

void Networking::send(const msg::Message &msg, TCPsocket sock) {
	int n = SDLNet_TCP_Send(sock, (char*) &msg, msg.size);
	if (n < msg.size)
		error();
}

msg::Message* Networking::recieve(Socket* sock) {
	msg::Message* msg;
	int r = socket->recv(msg, sock);
	if(r <= 0)
		return nullptr;
	else return msg;
}

msg::Message* Networking::recieve(TCPsocket sock) {
	int n = 0;
	int m = 0;
	while (n < sizeof(msg::msgSizeType)) {

		m = SDLNet_TCP_Recv(sock, buffer + n, sizeof(msg::msgSizeType) - n);
		if (m <= 0)
			return nullptr;
		n = n + m;
	}

	int size = *((msg::msgSizeType*) buffer);

	while (n < size) {
		m = SDLNet_TCP_Recv(sock, buffer + n, size - n);
		if (m <= 0)
			return nullptr;
		n = n + m;
	}
//	std::cout << n << " " << size << std::endl;
	return (msg::Message*) buffer;
}

bool Networking::client(const char *host, const char* port) {

	socket = new Socket(host, port);

	socket->bind();

	msg::Message mInp(msg::MsgId::_CONNECTED);

	send(mInp, socket);

	cout << "TEST before recieve\n";

	msg::Message* m = recieve(socket);

	cout << "TEST after recieve\n";

	if (m == nullptr) {
		error(); // something went wrong
	} else if (m->id == msg::_CONNECTED) { // M0
		clientId = static_cast<msg::ConnectedMsg*>(m)->clientId; // copy the identifier to id
	} else {
		cout << "false\n";
		return false;
	}

	cout << clientId << "\n";
	
	std::thread net_thread([this](){ clientThread(); });

	cout << "TEST client\n";
	
	// // a variable that represents the address of the server we want to connect to
	// IPaddress ip;

	// // fill in the address in 'ip'
	// if (SDLNet_ResolveHost(&ip, host, atoi(port)) < 0) {
	// 	error();
	// }

	// // establish the connection with the server
	// sock = SDLNet_TCP_Open(&ip);
	// if (!sock) {
	// 	error();
	// 	return false;
	// }

	// msg::Message *m = recieve(sock);

	// if (m == nullptr) {
	// 	error(); // something went wrong
	// } else if (m->id == msg::_CONNECTED) { // M0
	// 	clientId = static_cast<msg::ConnectedMsg*>(m)->clientId; // copy the identifier to id
	// } else {
	// 	return false;
	// }

	// // socket set for non-blocking communication
	// socketSet = SDLNet_AllocSocketSet(1);
	// SDLNet_TCP_AddSocket(socketSet, sock);

	return true;
}

void Networking::clientThread(){
	while(true){
		cout << "bucle\n";

		Socket* client;

		msg::Message *msg = recieve(client);

		if(!msg)
			continue;

		lastMsgs.push_back(msg);
	}
}

void Networking::server(const char * port) {

		std::cout << "Starting server at port " << port << std::endl;

		const char* h = "0.0.0.0";

		socket = new Socket(h, port);

		socket->bind();

		// an array for clients
		constexpr int MAX_CLIENTS_SOCK = 2;
		Socket* clientsSock[MAX_CLIENTS_SOCK];
		for (uint32_t i = 0; i < MAX_CLIENTS_SOCK; i++) {
			clientsSock[i] = nullptr;
		}

		while(true){

			Socket* client;

			//int r = socket.recv(msg, client);
			msg::Message* msg = recieve(client);

			if(msg == nullptr)
				continue;

			switch (msg->id)
        	{
            case msg::MsgId::_CONNECTED: {
				uint32_t j = 0;
				while (j < MAX_CLIENTS_SOCK && clientsSock[j] != nullptr)
					j++;
				if (j < MAX_CLIENTS_SOCK) {
					std::cout << "Client connected, assigned id " << j << std::endl;
					clientsSock[j] = client;

					msg::ConnectedMsg m(j);
					send(m, client);

				} else {
					// refuse connection (message type M1)
					msg::Message m(msg::_CONNECTION_REFUSED);
					send(m, client);
				}
                break;
            }
            case msg::MsgId::_CLIENT_DISCONNECTED: {
				int i = 0;
				for (i = 0; i < MAX_CLIENTS_SOCK; i++) {
					if (clientsSock[i] != nullptr){
						if(clientsSock[i] == client){
							delete clientsSock[i];
							clientsSock[i] = nullptr;
						}
					}
            	}
                if(i >= MAX_CLIENTS_SOCK){
					std::cout << "User not registered logged off\n";
                	break;
				}
				
				msg::ClientDisconnectedMsg m(i);
				for (int j = 0; j < MAX_CLIENTS_SOCK; j++) {
					if (clientsSock[j] != nullptr){
						send(m, clientsSock[j]);
					}
				}
				break;
        	}
            // case ChatMessage::MessageType::MESSAGE: {
            //     msgOut = msgInp;
            //     std::cout << msgInp.nick << " sent: " << msgInp.message << "\n";
            //     break;
            // }
            default: 
                std::cout << "Message Type unknown " << msg->id << "\n";
                continue;
		}

		//std::cout << "Connected users:\n";
        // auto it = clients.begin();
        // while(it != clients.end()) {
        //     // std::cout << *((*it).get()) << "\n";
        //     if(*((*it).get()) == *client){
        //         it++;
        //         continue;
        //     }
        //     socket.send(msgOut, *((*it).get()));
        //     it++;
        // }

		// // an array for clients
		// constexpr int MAX_CLIENTS = 2;
		// Socket* clients[MAX_CLIENTS];
		// for (uint32_t i = 0; i < MAX_CLIENTS; i++) {
		// 	clients[i] = new Socket(h, port);
		// 	clients[i]->bind();
		// }


		int p = atoi(port);

		// a variable that represents the address -- in this case only the port
		IPaddress ip;

		// fill in the address in 'ip' -- note that the 2nd parameter is 'nullptr'
		// which means that we want to use 'ip' to start a server
		if (SDLNet_ResolveHost(&ip, nullptr, p) < 0) {
			error();
		}

		// Since the host in 'ip' is 0 (we provided 'nullptr' above), SDLNet_TCP_Open starts
		// a server listening at the port specified in 'ip', and returns a socket for listening
		// to connection requests
		TCPsocket masterSocket = SDLNet_TCP_Open(&ip);
		if (!masterSocket) {
			error();
		}

		// We want to use non-blocking communication, the way to do this is via a socket set.
		// We add sockets to this set and then we can ask if any has some activity without blocking.
		// Non-blocking communication is the adequate one for video games!
		SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1000);

		// add the masterSocket to the set
		SDLNet_TCP_AddSocket(socketSet, masterSocket);

		// an array for clients
		constexpr int MAX_CLIENTS = 2;
		TCPsocket clients[MAX_CLIENTS];
		for (uint32_t i = 0; i < MAX_CLIENTS; i++) {
			clients[i] = nullptr;
		}

		while (true) {
			// The call to SDLNet_CheckSockets returns the number of sockets with activity
			// in socketSet. The 2nd parameter tells the method to wait up to SDL_MAX_UINT32
			// if there is no activity -- no need to put it 0 unless we really don't want to
			// block. With 0 it would consume CPU unnecessarily
			if (SDLNet_CheckSockets(socketSet, SDL_MAX_UINT32) > 0) {

				// if there is an activity in masterSocket we process it. Note that
				// before calling SDLNet_SocketReady we must have called SDLNet_CheckSockets
				if (SDLNet_SocketReady(masterSocket)) {

					// accept the connection (activity on master socket is always a connection
					// request, sending and receiving data is done via the socket returned by
					// SDLNet_TCP_Accept. This way we can serve several clients.
					TCPsocket client = SDLNet_TCP_Accept(masterSocket);

					// look for a free slot
					uint32_t j = 0;
					while (j < MAX_CLIENTS && clients[j] != nullptr)
						j++;

					// if there is a slot, add the client to the socketSet and send a connected message,
					// other say we are fully booked and close the connection
					if (j < MAX_CLIENTS) {
						std::cout << "Client connected, assigned id " << j << std::endl;
						clients[j] = client;
						SDLNet_TCP_AddSocket(socketSet, client);

						send(msg::ConnectedMsg(j), client);

					} else {
						// refuse connection (message type M1)
						msg::Message m(msg::_CONNECTION_REFUSED);
						send(m, client);
						SDLNet_TCP_Close(client);
					}
				}

				// check clients activity
				for (int i = 0; i < MAX_CLIENTS; i++) {
					if (clients[i] != nullptr && SDLNet_SocketReady(clients[i])) {
						msg::Message *m = recieve(clients[i]);

						// if result is zero, then the client has closed the connection
						// and if smaller than zero, then there was some error. In both
						// cases we close the connection
						if (m == nullptr) {
							std::cout << "Client " << i << " disconnected! " << std::endl;
							SDLNet_TCP_Close(clients[i]);
							SDLNet_TCP_DelSocket(socketSet, clients[i]);
							clients[i] = nullptr;

							// tell all clients that 'i' disconnected (message type M3)
							msg::ClientDisconnectedMsg m(i);
							for (uint32_t j = 0; j < MAX_CLIENTS; j++) {
								if (clients[j] != nullptr)
									send(m, clients[j]);
							}
						} else {
							for (uint32_t j = 0; j < MAX_CLIENTS; j++) {
								if (i != j && clients[j] != nullptr)
									send(*m, clients[j]);
							}
						}
					}
				}

			}
		}

		// finalize SDLNet
		SDLNet_Quit();

	}
}

void Networking::error() {
	cout << "ERROR IN NETWORKING\n";
}
