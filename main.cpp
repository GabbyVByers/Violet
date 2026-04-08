

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <string>

#define Vi Vi

namespace Vi {

    class Log {
    public:
        static void assert_message(bool statement, std::string message = "") {
            if (!statement) {
                std::cerr << "\033[31mAssert Failed\033[0m: " << message << "\n";
                std::terminate();
            }
        }
    };
}

namespace Vi {

    class Window {
    public:
        Window(std::string title, unsigned int width, unsigned int height) {

            GLFWwindow* window = glfwGetCurrentContext();
            Vi::Log::assert_message(window == nullptr, "GLFW context already exists!");

            GLuint status = glfwInit();
            Vi::Log::assert_message(status != NULL, "Failed to init GLFW!");

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
            Vi::Log::assert_message(window != nullptr, "Failed to create GLFW window!");

            glfwMakeContextCurrent(window);
            window = glfwGetCurrentContext();
            Vi::Log::assert_message(window != nullptr, "Failed to make GLFW current context!");

            status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            Vi::Log::assert_message(status != NULL, "Failed to load GLAD");

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

    {
        Vi::Window window = Vi::Window("Application Title", 1920, 1080);
    }
    Vi::Window window = Vi::Window("Application Title", 1920, 1080);


    while (window.is_open()) {
        window.poll_events();
        window.clear();
        window.display();
    }


    return 0;
}

