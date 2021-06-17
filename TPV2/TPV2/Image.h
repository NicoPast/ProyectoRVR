#pragma once

#include "Component.h"
#include "Texture.h"

struct Image: Component {
	Image(Texture *tex) :
			Component(ecs::Image), //
			tex_(tex) //
	{
	}
	Texture *tex_;
};

