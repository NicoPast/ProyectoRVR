#pragma once

#include "Entity.h"
#include "System.h"
#include "Vector2D.h"

class BulletsSystem: public System {
public:
	BulletsSystem();
	void update() override;
	void recieve(const msg::Message& msg) override;
private:
	void disableAll();
	void shoot(Vector2D pos, Vector2D vel, double w, double h);
};


