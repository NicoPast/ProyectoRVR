#pragma once
#include <SDL_net.h>
#include <iostream>
#include "messages.h"

class Networking {
public:
	Networking();
	virtual ~Networking();

	// for client use
	void send(const msg::Message &msg) {
		send(msg, sock);
	}

	msg::Message* recieve() {
		if (SDLNet_CheckSockets(socketSet, 0) > 0 && SDLNet_SocketReady(sock))
			return recieve(sock);
		else
			return nullptr;
	}

	// start server
	void server(int port);

	// start client
	bool client(char *host, int port);

	uint8_t getClientId() {
		return clientId;
	}

private:
	void error();
	void send(const msg::Message &msg, TCPsocket sock);
	msg::Message* recieve(TCPsocket sock);

	TCPsocket sock;
	SDLNet_SocketSet socketSet;

	char buffer[256];
	uint8_t clientId;
};

