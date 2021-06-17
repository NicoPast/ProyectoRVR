#pragma once

#include "Entity.h"
#include "System.h"



class RenderSystem: public System {
public:
	RenderSystem();
	void update() override;
private:
	void drawImage(Entity* e);
	void drawCtrlMessages();
	void drawScore();
	void drawNames();
};
