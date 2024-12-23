#pragma once

#include "glm/glm.hpp"
#include "render/Camera.h"
#include "Hitbox.h"

class Player {
public:
	Camera cam;
	Hitbox hitbox = Hitbox(glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(1.0f, 2.0f, 1.0f));
	glm::vec3 pos = glm::vec3(0.0f);
	glm::vec3 velocity = glm::vec3(0.0f);

private:
	glm::vec3 xzDirection = glm::vec3(0.0f);
	glm::vec3 lookingAt = glm::vec3(0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	float yaw = 0.0f, pitch = 0.0f;
	float speed = 1.0f;
	float gravity = 0.49f;
	
public:
	void updateVelocity(GLFWwindow* window, float deltaTime) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			velocity += speed * xzDirection;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			velocity -= speed * xzDirection;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			velocity += speed * glm::normalize(glm::cross(xzDirection, up));
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			velocity -= speed * glm::normalize(glm::cross(xzDirection, up));

		if (isAirborne())
			velocity.y -= gravity;
		else
			velocity.y = 0.0f;

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			velocity.y = 8.0f;

		velocity.x *= 0.9f;
		velocity.z *= 0.9f;
	}

	void updateMove(float deltaTime) {
		pos += velocity * deltaTime;
		pos.y = std::max(pos.y, 0.0f);

		hitbox.corner = glm::vec3(pos.x - 0.5f, pos.y, pos.z - 0.5f);

		cam.update(pos + glm::vec3(0.0f, 1.625f, 0.0f), lookingAt, yaw, pitch);
	}

	void processMouse(GLFWwindow* window, float x, float y) {
		static float lastMouseX = 0.0f;
		static float lastMouseY = 0.0f;
		static bool firstMouse = true;

		if (firstMouse) {
			lastMouseX = x;
			lastMouseY = y;
			firstMouse = false;
		}

		float deltaMouseX = x - lastMouseX;
		float deltaMouseY = lastMouseY - y;
		lastMouseX = x;
		lastMouseY = y;

		const float sensitivity = 0.04f;
		deltaMouseX *= sensitivity;
		deltaMouseY *= sensitivity;

		yaw += deltaMouseX;
		pitch += deltaMouseY;

		pitch = std::min(pitch, 89.99f);
		pitch = std::max(pitch, -89.99f);

		lookingAt = glm::normalize(glm::vec3(
			cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
			sin(glm::radians(pitch)),
			sin(glm::radians(yaw)) * cos(glm::radians(pitch))
		));

		xzDirection = glm::normalize(glm::vec3(
			cos(glm::radians(yaw)),
			0.0f,
			sin(glm::radians(yaw))
		));

		cam.update(pos, lookingAt, yaw, pitch);
	}

	bool isAirborne() const {
		return pos.y > 0.0f;
	}
};
