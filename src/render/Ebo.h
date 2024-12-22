#pragma once

#include "glad/glad.h"

class Ebo {
private:
	GLuint id;

public:
	Ebo() {
		glGenBuffers(1, &id);
	}

	void bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void data(const void* data, const GLuint size) const {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
};
