#pragma once

#include <cstring>

#include "Component.h"

struct CellInfo: Component {

	CellInfo(uint8_t cellId, uint8_t type) :
			Component(ecs::CellInfo), cellId(cellId), type(type) {
	}

	uint8_t cellId;
	uint8_t type;
};