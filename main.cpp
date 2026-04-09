

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <string>

#define Vi Vi

namespace Vi {

    class Logger {
    public:
        static std::string error_message(std::string message = "") {
            return "\033[31mCatastrophic Error\033[0m: " + message + "\n";
        }
    };

    class Window {
    public:
        Window(std::string title, unsigned int width, unsigned int height) {

            GLFWwindow* window = glfwGetCurrentContext();
            if (window != nullptr) {
                std::cerr << Logger::error_message("GLFW context already exists");
                std::terminate();
            }

            GLuint status = glfwInit();
            if (status == NULL) {
                std::cerr << Logger::error_message("Failed to initialize GLFW");
                std::terminate();
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
            if (window == nullptr) {
                std::cerr << Logger::error_message("Failed to create GLFW window");
                std::terminate();
            }

            glfwMakeContextCurrent(window);
            window = glfwGetCurrentContext();
            if (window == nullptr) {
                std::cerr << Logger::error_message("Failed to make GLFW current context");
                std::terminate();
            }

            status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            if (status == NULL) {
                std::cerr << Logger::error_message("Failed to load GLAD");
                std::terminate();
            }
            
            glViewport(0, 0, width, height);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_PROGRAM_POINT_SIZE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.FontGlobalScale = 2.0f;
            io.IniFilename = nullptr;
            ImGui::StyleColorsDark();
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 330");
        }

        ~Window() {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            glfwDestroyWindow(glfwGetCurrentContext());
            glfwTerminate();
        }

        bool is_open() {
            GLFWwindow* window = glfwGetCurrentContext();
            return !glfwWindowShouldClose(window);
        }

        void poll_events() {
            glfwPollEvents();
        }

        void clear() {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void display() {
            GLFWwindow* window = glfwGetCurrentContext();
            glfwSwapBuffers(window);
        }
    };
}

int main() {

    Vi::Window window = Vi::Window("Application Title", 1920, 1080);

    while (window.is_open()) {
        window.poll_events();
        window.clear();
        window.display();
    }

    return 0;
}

