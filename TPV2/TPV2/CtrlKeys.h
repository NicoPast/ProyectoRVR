#pragma once

#include <SDL_keyboard.h>
#include "Component.h"

struct CtrlKeys: Component {
	CtrlKeys(SDL_Keycode left, SDL_Keycode right, SDL_Keycode speedup,
			SDL_Keycode slowdown, SDL_Keycode shoot) :
			Component(ecs::CtrlKeys), //
			left(left), //
			right(right), //
			speedup(speedup), //
			slowdown(slowdown), //
			shoot(shoot), //
			lastShootTime(0) {
	}

	SDL_Keycode left;
	SDL_Keycode right;
	SDL_Keycode speedup;
	SDL_Keycode slowdown;
	SDL_Keycode shoot;
	Uint32 lastShootTime;
};
