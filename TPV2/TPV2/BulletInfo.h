#pragma once

#include <cstring>

#include "Component.h"

struct BulletInfo: Component {

	BulletInfo(uint8_t bulletId, uint8_t bounces) :
			Component(ecs::BulletInfo), bulletId(bulletId), bounces(bounces), position(-100, -100), direction(0, 0) {
	}

	uint8_t bulletId;
	uint8_t bounces;
	Vector2D position;
	Vector2D direction;
};