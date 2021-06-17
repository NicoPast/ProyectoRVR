#pragma once

#include "System.h"

class CollisionSystem: public System {
public:
	CollisionSystem();
	virtual ~CollisionSystem();
	void update() override;
};

