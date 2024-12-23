#pragma once

#include <iostream>
#include <vector>

#include "Player.h"
#include "SolidRectangle.h"

class World {
public:
	Player player;
	std::vector<SolidRectangle> obstacles;

	void update(GLFWwindow* ptr, float deltaTime) {
		static int hiddenCounterLol = 0;

		player.updateVelocity(ptr, deltaTime);

		for (const auto& obstacle : obstacles)
			player.velocity = obstacle.hitbox.collide(player.hitbox, player.velocity, deltaTime);

		player.updateMove(deltaTime);

		std::cout << player.pos.x << ' ' << player.pos.y << ' ' << player.pos.z << '\n';
	}
};
