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
		const glm::vec3 d1 = o11 - c22;
		const glm::vec3 d2 = o22 - c11;

		if (!willCollide(collider, velocity, deltaTime))
			return velocity;

		glm::vec3 dvel = velocity;

		if (d1.x > 0.0f)
			dvel.x = std::min(dvel.x * deltaTime, d1.x);
		else if (d2.x < 0.0f)
			dvel.x = std::max(dvel.x * deltaTime, d2.x);

		if (d1.y > 0.0f)
			dvel.y = std::min(dvel.y * deltaTime, d1.y);
		else if (d2.y < 0.0f)
			dvel.y = std::max(dvel.y * deltaTime, d2.y);

		if (d1.z > 0.0f)
			dvel.z = std::min(dvel.z * deltaTime, d1.z);
		else if (d2.z < 0.0f)
			dvel.z = std::max(dvel.z * deltaTime, d2.z);

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
