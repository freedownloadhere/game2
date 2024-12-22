#include <iostream>

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "render/Shader.h"
#include "render/Vao.h"
#include "render/Vbo.h"
#include "render/Ebo.h"
#include "render/Camera.h"
#include "render/Texture2D.h"
#include "Player.h"

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

static Player player;

static void cursorPosCallback(GLFWwindow* window, double x, double y) {
	player.processMouse(window, x, y);
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
	glEnable(GL_DEPTH_TEST);
	Shader shader("shaders/default.vert", "shaders/default.frag");
	Vao vao(5 * sizeof(float));
	Vbo vbo;
	Ebo ebo;
	Texture2D tex("res/parchet.jpg", GL_RGB);
	vao.bind();
	vbo.bind();
	ebo.bind();
	vbo.data(epicFloor, sizeof(epicFloor));
	ebo.data(indices, sizeof(indices));
	vao.attrib(3, GL_FLOAT, sizeof(float)); // pos
	vao.attrib(2, GL_FLOAT, sizeof(float)); // texcoord
	shader.use();
	tex.bind(0);
	shader.setInt("tex", 0);
	float lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		const float currentTime = glfwGetTime();
		const float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		player.update(window, deltaTime);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 view = player.cam.getViewMat();
		glm::mat4 proj = player.cam.getPerspective(1280, 720);
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("proj", proj);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.2f, 0.6f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
	}
	return 0;
}