#include "ecs.h"
#include "Manager.h"
#include "Entity.h"
#include "Transform.h"
#include "Image.h"
#include "CtrlKeys.h"
#include "BulletsSystem.h"
#include "FighterInfo.h"
#include "FightersSystem.h"
#include "GameCtrlSystem.h"
#include "MapSystem.h"

#include <cstdint>
#include <algorithm>

using ecs::CmpId;

MapSystem::MapSystem() :
		System(ecs::_sys_Map) {
}

MapSystem::~MapSystem() {
}

void MapSystem::init() {
	// TO DO
	// construye las celdas en funcion de las que haya en celdas y columnas
	//BulletsPool::init(100);
	
	// for (cols * rows) -> addEntity->Celda
	// estas entidades en funcion de su col y row, pos
	// y en funcion de with y height del mapa sus dimensiones
}

void MapSystem::update() {
	auto gameState =
			mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->getState();
	if (gameState != GameCtrlSystem::RUNNING)
		return;
	// TO DO: cada x tiempo volver a spawnear ladrillos 
}

void MapSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_START_ROUND: {
		break;
	}
	default:
		break;
	}
}