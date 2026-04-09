
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

    class Vertex;
    class Transform;
    class Camera;

    class Texture;
    class Material;
    class Mesh;

    class Keyboard;
    class Mouse;
    class Window;

    /* Vertex, Transform, Camera */

    class Vertex {
    public:
        Vertex() = default;
        Vec3d position = Vec3d();
        Color color = Color::white();
        Vec2f tex_coord = Vec2f();
    };

    class Transform {
    public:
        Transform() = default;
        double scale = 1.0;
        Vec3d position = Vec3d();
        Quat orientation = Quat();
        Mat4 view_matrix() const;
        Mat4 projection_matrix() const;
    };

    class Camera {
    public:
        Camera() = default;
        double far = 100.0f;
        double near = 0.1f;
        double fov = 70.0f;
        Transform transform = Transform();
        Vec3d forward() const;
        Vec3d up() const;
        Vec3d right() const;
    };

    /* Texture, Material, Mesh */

    class Texture {
    public:
        Texture(const std::string& = "");
        Texture(Texture&&) noexcept;
        Texture& operator = (Texture&&) noexcept;
        ~Texture();
    private:
        friend Window;
        GLuint texture = NULL;
        Texture(const Texture&) = delete;
        Texture& operator = (const Texture&) = delete;
    };

    class Material {
    public:
        Material(const std::string& = "default", GLenum = GL_TRIANGLES);
        Material(Material&&) noexcept;
        Material& operator = (Material&&) noexcept;
        ~Material();
    private:
        friend Window;
        GLuint vao = NULL;
        GLuint vbo = NULL;
        GLuint shader = NULL;
        GLuint primitive = NULL;
        Material(const Material&) = delete;
        Material& operator = (const Material&) = delete;
    };

    class Mesh {
    public:
        Texture texture = Texture();
        Material material = Material();
        Transform transform = Transform();
        std::vector<Vertex> vertices = {};
        void paint(const Color&);
    };

    /* Keyboard, Mouse, Window */

    class Keyboard {
    public:
        bool pressed(int, int) const;
        bool pressing(int) const;
    private:
        friend Window;
        struct KeyboardEvent { int key; int scancode; int action; int mods; };
        std::vector<KeyboardEvent> keyboard_events = {};
        void reset();
    };

    class Mouse {
    public:
        Vec2d position() const;
        Vec2d velocity() const;
        bool pressing(int) const;
        bool clicked(int, int) const;
        double scroll() const;
    private:
        friend Window;
        Mouse() = default;
        struct MouseEvent { int button; int action; int mods; };
        struct ScrollEvent { double xoffset; double yoffset; };
        Vec2d pos = Vec2d();
        Vec2d vel = Vec2d();
        std::vector<MouseEvent> mouse_events = {};
        std::vector<ScrollEvent> scroll_events = {};
        void reset();
    };

    class Window {
    public:
        Window(std::string, int, int);
        ~Window();
        Vec2i size();
        void vsync(bool);
        bool is_open();
        void poll_events();
        void clear(const Color&);
        void draw(const Mesh&, const Camera&);
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

