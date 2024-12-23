#include <iostream>

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "render/Shader.h"
#include "render/Vao.h"
#include "render/Vbo.h"
#include "render/Ebo.h"
#include "render/Camera.h"
#include "render/Texture2D.h"
#include "World.h"

const float epicFloor[] = {
	 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left 
};

const int indices[] = {
	0, 1, 2, 
	2, 3, 0
};

static World world;

static void cursorPosCallback(GLFWwindow* window, double x, double y) {
	world.player.processMouse(window, x, y);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	auto window = glfwCreateWindow(1280, 720, "help", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	gladLoadGL();
	glViewport(0, 0, 1280, 720);

	Shader shader("shaders/default.vert", "shaders/default.frag");
	Shader wireframe("shaders/wireframe.vert", "shaders/wireframe.frag");
	Vao vao(5 * sizeof(float));
	Vbo vbo;
	Ebo ebo;
	Texture2D tex("res/parchet.jpg", GL_RGB);

	vao.bind();
	vbo.bind();
	ebo.bind();
	vbo.data(epicFloor, sizeof(epicFloor));
	ebo.data(indices, sizeof(indices));
	vao.attrib(3, GL_FLOAT, sizeof(float));
	vao.attrib(2, GL_FLOAT, sizeof(float));

	shader.use();
	shader.setInt("tex", 0);
	tex.bind(0);

	world.obstacles.push_back(SolidRectangle(Hitbox(glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(1.0f, 0.5f, 1.0f))));
	world.obstacles.push_back(SolidRectangle(Hitbox(glm::vec3(2.0f, -1.0f, 2.0f), glm::vec3(1.0f, 4.0f, 1.0f))));

	float lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.2f, 0.6f, 1.0f);

		const float currentTime = glfwGetTime();
		const float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		world.update(window, deltaTime);

		glEnable(GL_DEPTH_TEST);
		shader.use();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 view = world.player.cam.getViewMat();
		glm::mat4 proj = world.player.cam.getPerspective(1280, 720);
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("proj", proj);
		vbo.data(epicFloor, sizeof(epicFloor));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		for (const auto& obstacle : world.obstacles) {
			const auto& vertices = obstacle.hitbox.getVertices();
			vbo.data(vertices.data(), vertices.size() * sizeof(float));

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, obstacle.hitbox.corner);
			model = glm::scale(model, obstacle.hitbox.length);
			shader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		const auto& vertices = world.player.hitbox.getVertices();
		vbo.data(vertices.data(), vertices.size() * sizeof(float));

		glDisable(GL_DEPTH_TEST);
		wireframe.use();
		model = glm::mat4(1.0f);
		model = glm::translate(model, world.player.hitbox.corner);
		model = glm::scale(model, world.player.hitbox.length);
		wireframe.setMat4("model", model);
		wireframe.setMat4("view", view);
		wireframe.setMat4("proj", proj);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glfwSwapBuffers(window);
	}
	return 0;
}