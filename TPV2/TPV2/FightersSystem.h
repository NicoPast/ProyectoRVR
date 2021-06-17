#pragma once

#include <SDL.h>
#include <cstdint>

#include "Entity.h"
#include "System.h"
#include "Vector2D.h"

class FightersSystem: public System {
public:
	FightersSystem();
	virtual ~FightersSystem();
	void init() override;
	void update() override;
	void recieve(const msg::Message& msg) override;
private:
	void resetFighterPositions();
	void updateFighter(Entity *e);
	Entity *fighter0_;
	Entity *fighter1_;
};

