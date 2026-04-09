
/*
    Material.cpp
*/

#include "Violet.h"
#include <fstream>
#include <sstream>

namespace Vi {

    /* Public */

    Material::Material(const std::string& shader_path, GLenum type) {
        GLFWwindow* window = glfwGetCurrentContext();
        if (window == nullptr) {
            std::cerr << Logger::error_message("GLFW context does not exist");
            std::terminate();
        }

        primitive = type;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));
        glEnableVertexAttribArray(2);

		auto load = [](std::string path) -> std::string {
			std::ifstream file(path);
			std::stringstream buffer;
			buffer << file.rdbuf();
			return buffer.str();
		};

		std::string vert_source = load(shader_path + ".vert");
		std::string frag_source = load(shader_path + ".frag");
		const char* vert_c_str = vert_source.c_str();
		const char* frag_c_str = frag_source.c_str();

		GLuint vert_program = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vert_program, 1, &vert_c_str, nullptr);
		glCompileShader(vert_program);
		GLint success;
		glGetShaderiv(vert_program, GL_COMPILE_STATUS, &success);
		if (success == NULL) {
			Logger::error_message("Failed to compile vertex shader");
			std::terminate();
		}

		GLuint frag_program = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(frag_program, 1, &frag_c_str, nullptr);
		glCompileShader(frag_program);
		glGetShaderiv(frag_program, GL_COMPILE_STATUS, &success);
		if (success == NULL) {
			Logger::error_message("Failed to compile fragment shader");
			std::terminate();
		}

		shader = glCreateProgram();
		glAttachShader(shader, vert_program);
		glAttachShader(shader, frag_program);
		glLinkProgram(shader);
		glDeleteShader(vert_program);
		glDeleteShader(frag_program);
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (success == NULL) {
			Logger::error_message("Failed to link shader program");
			std::terminate();
		}
    }

	Material::Material(Material&& other) noexcept {
		if (this == &other)
			return;

		vao = other.vao;
		vbo = other.vbo;
		shader = other.shader;
		primitive = other.primitive;
		other.vao = NULL;
		other.vbo = NULL;
		other.shader = NULL;
		other.primitive = NULL;
	}

	Material& Material::operator = (Material&& other) noexcept {
		if (this == &other)
			return *this;

		if (vao != NULL) {
			glDeleteVertexArrays(1, &vao);
			vao = NULL;
		}
		if (vbo != NULL) {
			glDeleteBuffers(1, &vbo);
			vbo = NULL;
		}
		if (shader != NULL) {
			glDeleteProgram(shader);
			shader = NULL;
		}

		vao = other.vao;
		vbo = other.vbo;
		shader = other.shader;
		primitive = other.primitive;
		other.vao = NULL;
		other.vbo = NULL;
		other.shader = NULL;
		other.primitive = NULL;
	}

	Material::~Material() {
		if (vao != NULL) {
			glDeleteVertexArrays(1, &vao);
			vao = NULL;
		}
		if (vbo != NULL) {
			glDeleteBuffers(1, &vbo);
			vbo = NULL;
		}
		if (shader != NULL) {
			glDeleteProgram(shader);
			shader = NULL;
		}
	}
}

