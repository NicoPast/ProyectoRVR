#pragma once

#include "System.h"

class NetworkingSystem: public System {
public:
	NetworkingSystem();
	virtual ~NetworkingSystem();
	void recieve(const msg::Message &msg) override;
	void update() override;
};

