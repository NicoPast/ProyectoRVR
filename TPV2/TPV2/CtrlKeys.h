#pragma once

#include <SDL_keyboard.h>
#include "Component.h"

struct CtrlKeys: Component {
	CtrlKeys(SDL_Keycode left, SDL_Keycode right, SDL_Keycode up,
			SDL_Keycode down, SDL_Keycode shoot) :
			Component(ecs::CtrlKeys), //
			left(left), //
			right(right), //
			up(up), //
			down(down), //
			shoot(shoot), //
			lastShootTime(0) {
	}

	SDL_Keycode left;
	SDL_Keycode right;
	SDL_Keycode up;
	SDL_Keycode down;
	SDL_Keycode shoot;
	Uint32 lastShootTime;
};
