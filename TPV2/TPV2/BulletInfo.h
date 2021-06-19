#pragma once

#include <cstring>

#include "Component.h"

struct BulletInfo: Component {

	BulletInfo(uint8_t bulletId, uint8_t bounces) :
			Component(ecs::BulletInfo), bulletId(bulletId), bounces(bounces) {
	}

	uint8_t bulletId;
	uint8_t bounces;
};