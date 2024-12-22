#include <iostream>

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "render/Shader.h"
#include "render/Vao.h"
#include "render/Vbo.h"
#include "render/Camera.h"

const float triangleVerts[18] = {
	 0.0f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f
};

static Camera cam;

static void cursorPosCallback(GLFWwindow* window, double x, double y) {
	cam.processMouse(window, x, y);
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
	Vao vao(6 * sizeof(float));
	Vbo vbo;
	vao.bind();
	vbo.bind();
	vbo.data(triangleVerts, sizeof(triangleVerts));
	vao.attrib(3, GL_FLOAT, sizeof(float));
	vao.attrib(3, GL_FLOAT, sizeof(float));
	shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	shader.setMat4("model", model);
	float lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		const float currentTime = glfwGetTime();
		const float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		cam.processKeyboard(window, deltaTime);
		glm::mat4 view = cam.getViewMat();
		glm::mat4 proj = cam.getPerspective(1280, 720);
		shader.setMat4("view", view);
		shader.setMat4("proj", proj);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.2f, 0.6f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
	}
	return 0;
}