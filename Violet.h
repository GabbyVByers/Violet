
/*
    Violet.h
*/

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Logger.h"
#include "Types.h"
#include <iostream>
#include <vector>
#include <string>

#define Vi Vi
namespace Vi {

    class Keyboard;
    class Mouse;
    class Window;

    class Keyboard {
    public:
        bool pressed(int, int) const;
        bool pressing(int) const;
    private:
        friend Window;
        struct KeyboardEvent { int key; int scancode; int action; int mods; };
        Keyboard() = default;
        std::vector<KeyboardEvent> keyboard_events;
        void reset();
    };

    class Mouse {
    public:
        Vec2d position() const;
        Vec2d velocity() const;
        bool  pressing(int) const;
        bool  clicked(int, int) const;
        float scroll() const;
    private:
        friend Window;
        struct MouseEvent { int button; int action; int mods; };
        struct ScrollEvent { double xoffset; double yoffset; };
        Vec2d pos;
        Vec2d vel;
        std::vector<MouseEvent> mouse_events;
        std::vector<ScrollEvent> scroll_events;
        Mouse();
        void reset();
    };

    class Window {
    public:
        Window(std::string, int, int);
        ~Window();
        Vec2i size();
        bool is_open();
        void poll_events();
        void clear(const Color&);
        void display();
        static Mouse& mouse();
        static Keyboard& keyboard();
    private:
        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator = (const Window&) = delete;
        Window& operator = (Window&&) = delete;
        static void callback_window_resize(GLFWwindow*, int, int);
        static void callback_keyboard(GLFWwindow*, int, int, int, int);
        static void callback_mouse(GLFWwindow*, int, int, int);
        static void callback_mousescroll(GLFWwindow*, double, double);
    };
}

