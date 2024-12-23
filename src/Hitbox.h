#pragma once

#include "glm/glm.hpp"

class Hitbox {
public:
	Hitbox(const glm::vec3& _corner, const glm::vec3& _length)
		: corner(_corner), length(_length) {};

	glm::vec3 corner;
	glm::vec3 length;

	bool willCollide(const Hitbox& collider, glm::vec3 velocity, float deltaTime) const {
		const glm::vec3 thisPos1 = corner;
		const glm::vec3 colliderPos1 = collider.corner + (velocity * deltaTime);
		const glm::vec3 thisPos2 = thisPos1 + length;
		const glm::vec3 colliderPos2 = colliderPos1 + collider.length;
		if ((thisPos1.x <= colliderPos1.x && colliderPos1.x <= thisPos2.x) || (thisPos1.x <= colliderPos2.x && colliderPos2.x <= thisPos2.x))
			if ((thisPos1.y <= colliderPos1.y && colliderPos1.y <= thisPos2.y) || (thisPos1.y <= colliderPos2.y && colliderPos2.y <= thisPos2.y))
				if ((thisPos1.z <= colliderPos1.z && colliderPos1.z <= thisPos2.z) || (thisPos1.z <= colliderPos2.z && colliderPos2.z <= thisPos2.z))
					return true;
		return false;
	}

	glm::vec3 collide(const Hitbox& collider, glm::vec3 velocity, float deltaTime) const {
		const glm::vec3 o11 = corner;
		const glm::vec3 c11 = collider.corner;
		const glm::vec3 o22 = o11 + length;
		const glm::vec3 c22 = c11 + collider.length;

		if (!willCollide(collider, velocity, deltaTime))
			return velocity;

		glm::vec3 dvel = velocity * deltaTime;

		const float dx1 = o11.x - c22.x;
		const float dx2 = o22.x - c11.x;
		if (dx1 > 0.0f)
			dvel.x = std::min(dvel.x, dx1);
		else if (dx2 < 0.0f)
			dvel.x = std::max(dvel.x, dx2);

		const float dy1 = o11.y - c22.y;
		const float dy2 = o22.y - c11.y;
		if (dy1 > 0.0f)
			dvel.y = std::min(dvel.y, dy1);
		else if (dy2 < 0.0f)
			dvel.y = std::max(dvel.y, dy2);

		const float dz1 = o11.z - c22.z;
		const float dz2 = o22.z - c11.z;
		if (dz1 > 0.0f)
			dvel.z = std::min(dvel.z, dz1);
		else if (dz2 < 0.0f)
			dvel.z = std::max(dvel.z, dz2);

		return dvel;
	}

	std::vector<float> getVertices() const {
		return {
			 0.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			 1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			 1.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			 0.0f,  0.0f,  0.0f,  0.0f, 0.0f,

			 0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
			 1.0f,  0.0f,  1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
			 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
			 0.0f,  1.0f,  1.0f,  0.0f, 1.0f,
			 0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

			 0.0f,  1.0f,  1.0f,  1.0f, 0.0f,
			 0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			 0.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
			 0.0f,  1.0f,  1.0f,  1.0f, 0.0f,

			 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			 1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 1.0f,  0.0f,  1.0f,  0.0f, 0.0f,
			 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

			 0.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			 1.0f,  0.0f,  1.0f,  1.0f, 0.0f,
			 1.0f,  0.0f,  1.0f,  1.0f, 0.0f,
			 0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
			 0.0f,  0.0f,  0.0f,  0.0f, 1.0f,

			 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			 1.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
			 0.0f,  1.0f,  1.0f,  0.0f, 0.0f,
			 0.0f,  1.0f,  0.0f,  0.0f, 1.0f
		};
	}
};
