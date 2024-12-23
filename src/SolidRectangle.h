#pragma once

#include <vector>

#include "Hitbox.h"

class SolidRectangle {
public:
	SolidRectangle(const Hitbox& _hitbox) : hitbox(_hitbox) {};
	Hitbox hitbox;
};
