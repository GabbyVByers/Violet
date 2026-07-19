
/* material.cpp */

#include "rendering.h"

namespace Vi {

	/* Public */

	Material::Material() {
		generate();
	}

	Material::Material(const Material&) {
		generate();
	}

	Material::Material(Material&& other) noexcept {
		VAO = std::move(other.VAO);
		VBO = std::move(other.VBO);
		other.VAO = 0;
		other.VBO = 0;
	}

	Material& Material::operator = (const Material&) {
		destroy();
		generate();
		return *this;
	}

	Material& Material::operator = (Material&& other) noexcept {
		if (this == &other)
			return *this;
		destroy();
		VAO = std::move(other.VAO);
		VBO = std::move(other.VBO);
		other.VAO = 0;
		other.VBO = 0;
		return *this;
	}

	Material::~Material() {
		destroy();
	}

	/* Private */

	void Material::generate() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, texCoord)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));
		glEnableVertexAttribArray(2);
	}

	void Material::destroy() {
		if (VAO != 0) { glDeleteVertexArrays(1, &VAO); VAO = 0; }
		if (VBO != 0) { glDeleteBuffers(1, &VBO); VBO = 0; }
	}
}

