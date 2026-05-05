
/*
    Mouse.cpp
*/

#include "../Rendering.h"

namespace Vi {

    /* Public */

    Vec2d Mouse::position() const {
        return pos;
    }

    Vec2d Mouse::velocity() const {
        return vel;
    }

    bool Mouse::pressing(int button) const {
        GLFWwindow* window = glfwGetCurrentContext();
        if (window == nullptr) {
            Log::error("GLFW context does not exist");
        }
        return glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

    bool Mouse::pressed(int button, int action) const {
        for (const MouseEvent& event : mouse_events) {
            if (button == event.button) {
                if (action == event.action) {
                    return true;
                }
            }
        }
        return false;
    }

    double Mouse::scroll() const {
        double scroll = 0.0;
        for (const ScrollEvent& event : scroll_events) {
            scroll += event.yoffset;
        }
        return scroll;
    }

    void Mouse::cursor(int cursor_setting) {
        GLFWwindow* window = glfwGetCurrentContext();
        if (window == nullptr) {
            Log::error("GLFW context does not exist");
        }
        // GLFW_CURSOR_NORMAL
        // GLFW_CURSOR_HIDDEN
        // GLFW_CURSOR_DISABLED
        glfwSetInputMode(window, GLFW_CURSOR, cursor_setting);
    }

    bool Mouse::imgui_captured() const {
        const ImGuiIO& io = ImGui::GetIO();
        return io.WantCaptureMouse;
    }

    /* Private */

    void Mouse::reset() {
        GLFWwindow* window = glfwGetCurrentContext();
        if (window == nullptr) {
            Log::error("GLFW context does not exist");
        }
        double x, y; glfwGetCursorPos(window, &x, &y);
        Vec2d new_pos = Vec2d(x, y);
        vel = new_pos - pos;
        pos = new_pos;
        mouse_events.clear();
        scroll_events.clear();
    }
}

