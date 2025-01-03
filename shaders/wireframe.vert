#version 330 core
out vec4 fragPos;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
	fragPos = vec4(aPos, 1.0f);
	gl_Position = proj * view * model * vec4(aPos, 1.0f);
}