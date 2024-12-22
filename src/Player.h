#pragma once

#include "glm/glm.hpp"
#include "render/Camera.h"

class Player {
public:
	Camera cam;

private:
	glm::vec3 pos;
	glm::vec3 xzDirection;
	glm::vec3 lookingAt;
	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	float yaw, pitch;
	float speed = 1.0f;
	float gravity = 9.8f;
	
public:
	void update(GLFWwindow* window, float deltaTime) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			velocity += speed * xzDirection;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			velocity -= speed * xzDirection;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			velocity += speed * glm::normalize(glm::cross(xzDirection, up));
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			velocity -= speed * glm::normalize(glm::cross(xzDirection, up));

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			if (!isAirborne())
				velocity.y = 5.0f;

		velocity.y -= gravity * deltaTime;

		velocity.x *= 0.9f;
		velocity.z *= 0.9f;

		pos += velocity * deltaTime;
		pos.y = std::max(pos.y, 0.0f);

		cam.update(pos, lookingAt, yaw, pitch);
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
