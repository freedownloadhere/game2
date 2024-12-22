#version 330 core
out vec4 fragCol;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
	gl_Position = proj * view * model * vec4(aPos, 1.0f);
	fragCol = vec4(aCol, 1.0f);
}