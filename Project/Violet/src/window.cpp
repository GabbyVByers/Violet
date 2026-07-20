
/******************/
/*   window.cpp   */
/******************/

#include "rendering.h"
#include <cassert>
#include <fstream>
#include <sstream>

namespace Vi {

	/* Public */

	void Window::create(const char* title, int width, int height) {
		GLFWwindow* window = glfwGetCurrentContext();
		assert(window == nullptr);
		
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwMakeContextCurrent(window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSwapInterval((int)false);
		
		glViewport(0, 0, width, height);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_PROGRAM_POINT_SIZE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glfwSetFramebufferSizeCallback(window, callbackResize);
		glfwSetKeyCallback(window, callbackKeyboard);
		glfwSetMouseButtonCallback(window, callbackMouse);
		glfwSetScrollCallback(window, callbackScroll);

		auto load = [](std::string path) -> std::string {
			std::ifstream file(path);
			assert(file);
			std::stringstream buffer;
			buffer << file.rdbuf();
			return buffer.str();
		};

		std::string root = __FILE__;
		std::string vert_source = load(root + "/../../glsl/default.vert");
		std::string frag_source = load(root + "/../../glsl/default.frag");
		const char* vert_c_str = vert_source.c_str();
		const char* frag_c_str = frag_source.c_str();

		GLint success{};
		GLuint vert_program = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vert_program, 1, &vert_c_str, nullptr);
		glCompileShader(vert_program);
		glGetShaderiv(vert_program, GL_COMPILE_STATUS, &success);
		assert(success);

		GLuint frag_program = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(frag_program, 1, &frag_c_str, nullptr);
		glCompileShader(frag_program);
		glGetShaderiv(frag_program, GL_COMPILE_STATUS, &success);
		assert(success);

		assert(glslShaderProgramID == 0);
		glslShaderProgramID = glCreateProgram();
		glAttachShader(glslShaderProgramID, vert_program);
		glAttachShader(glslShaderProgramID, frag_program);
		glLinkProgram(glslShaderProgramID);
		glDeleteShader(vert_program);
		glDeleteShader(frag_program);
		glGetProgramiv(glslShaderProgramID, GL_LINK_STATUS, &success);
		assert(success);
	}

	void Window::destroy() {
		GLFWwindow* window = glfwGetCurrentContext();
		assert(window != nullptr);
		glDeleteProgram(glslShaderProgramID);
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::vsync(bool interval) {
		glfwSwapInterval(int(interval));
	}

	bool Window::isOpen() {
		GLFWwindow* window = glfwGetCurrentContext();
		assert(window != nullptr);
		return !glfwWindowShouldClose(window);
	}

	void Window::pollEvents() {
		Mouse::mouse_events.clear();
		Mouse::scroll_events.clear();
		Keyboard::keyboard_events.clear();
		glfwPollEvents();
	}

	void Window::clear(Color color) {
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::draw(const Mesh& mesh) {
		const GLuint VAO = mesh.material.VAO;
		const GLuint VBO = mesh.material.VBO;
		const GLuint glTextureID = mesh.texture.glTextureID;
		const std::vector<Vertex>& vertices = mesh.vertices;
		if (vertices.size() == 0) return;

		glUseProgram(glslShaderProgramID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, glTextureID);
		glUniform1i(glGetUniformLocation(glslShaderProgramID, "ourTexture"), 0);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		Matrix<double> M = mesh.modelMatrix();
		Matrix<double> V = Camera::viewMatrix();
		Matrix<double> P = Camera::projectionMatrix();
		Matrix<double> MVP = P * V * M;
		Matrix<float> glmvp = static_cast<Matrix<float>>(MVP);
		glUniformMatrix4fv(glGetUniformLocation(glslShaderProgramID, "uModelViewProject"), 1, GL_TRUE, glmvp.get());

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());
	}

	//void Window::draw(const Sprite& sprite) {
	//
	//}

	//void Window::draw(const Text& text) {
	//
	//}

	void Window::display() {
		GLFWwindow* window = glfwGetCurrentContext();
		assert(window != nullptr);
		glfwSwapBuffers(window);
	}

	/* Private */

	void Window::callbackResize(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	void Window::callbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Keyboard::KeyboardEvent event = {
			.key = key,
			.scancode = scancode,
			.action = action,
			.mods = mods
		};
		Keyboard::keyboard_events.push_back(event);
	}

	void Window::callbackMouse(GLFWwindow* window, int button, int action, int mods) {
		Mouse::MouseEvent event = {
			.button = button,
			.action = action,
			.mods = mods
		};
		Mouse::mouse_events.push_back(event);
	}

	void Window::callbackScroll(GLFWwindow* window, double xoffset, double yoffset) {
		Mouse::ScrollEvent event = {
			.xoffset = xoffset,
			.yoffset = yoffset,
		};
		Mouse::scroll_events.push_back(event);
	}
}

