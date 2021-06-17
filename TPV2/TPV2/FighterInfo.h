#pragma once

#include <cstring>

#include "Component.h"

struct FighterInfo: Component {

	FighterInfo(uint8_t fighterId) :
			Component(ecs::FighterInfo), fighterId(fighterId) {
	}

	uint8_t fighterId;
};

