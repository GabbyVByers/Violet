
/*
    rendering.h
*/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <vector>
#include <string>

#ifndef Vi
#define Vi Vi
#endif // Vi

//|--------------------------------------------------------
//| [Section] 2D & 3D Vectors for ints, floats, & doubles
//|--------------------------------------------------------

namespace Vi {

    class Vec2i;
    class Vec2f;
    class Vec2d;
    class Vec3i;
    class Vec3f;
    class Vec3d;
    class Quat; // Fwrd Dec

    class Vec2i {
    public:
        int x{}, y{};
        double length() const;
        Vec2i operator + (const Vec2i&) const;
        Vec2i operator - (const Vec2i&) const;
        Vec2i operator * (const int) const;
        Vec2i operator / (const int) const;
        Vec2i& operator += (const Vec2i&);
        Vec2i& operator -= (const Vec2i&);
        Vec2i& operator *= (const int);
        Vec2i& operator /= (const int);
        operator Vec2f() const;
        operator Vec2d() const;
    };

    class Vec2f {
    public:
        float x{}, y{};
        float length() const;
        Vec2f normalized() const;
        Vec2f operator + (const Vec2f&) const;
        Vec2f operator - (const Vec2f&) const;
        Vec2f operator * (const float) const;
        Vec2f operator / (const float) const;
        Vec2f& operator += (const Vec2f&);
        Vec2f& operator -= (const Vec2f&);
        Vec2f& operator *= (const float);
        Vec2f& operator /= (const float);
        operator Vec2i() const;
        operator Vec2d() const;
    };

    class Vec2d {
    public:
        double x{}, y{};
        double length() const;
        Vec2d normalized() const;
        Vec2d operator + (const Vec2d&) const;
        Vec2d operator - (const Vec2d&) const;
        Vec2d operator * (const double) const;
        Vec2d operator / (const double) const;
        Vec2d& operator += (const Vec2d&);
        Vec2d& operator -= (const Vec2d&);
        Vec2d& operator *= (const double);
        Vec2d& operator /= (const double);
        operator Vec2i() const;
        operator Vec2f() const;
    };

    class Vec3i {
    public:
        int x{}, y{}, z{};
        double length() const;
        Vec3i operator + (const Vec3i&) const;
        Vec3i operator - (const Vec3i&) const;
        Vec3i operator * (const int) const;
        Vec3i operator / (const int) const;
        Vec3i& operator += (const Vec3i&);
        Vec3i& operator -= (const Vec3i&);
        Vec3i& operator *= (const int);
        Vec3i& operator /= (const int);
        operator Vec3f() const;
        operator Vec3d() const;
    };

    class Vec3f {
    public:
        float x{}, y{}, z{};
        float length() const;
        Vec3f normalized() const;
        Vec3f operator + (const Vec3f&) const;
        Vec3f operator - (const Vec3f&) const;
        Vec3f operator * (const float) const;
        Vec3f operator / (const float) const;
        Vec3f& operator += (const Vec3f&);
        Vec3f& operator -= (const Vec3f&);
        Vec3f& operator *= (const float);
        Vec3f& operator /= (const float);
        operator Vec3i() const;
        operator Vec3d() const;
    };

    class Vec3d {
    public:
        double x{}, y{}, z{};
        double length() const;
        Vec3d normalized() const;
        Vec3d rotated_around(const Vec3d&, double) const;
        Vec3d rotated_using(const Quat&) const;
        Vec3d operator + (const Vec3d&) const;
        Vec3d operator - (const Vec3d&) const;
        Vec3d operator * (const double) const;
        Vec3d operator / (const double) const;
        Vec3d& operator += (const Vec3d&);
        Vec3d& operator -= (const Vec3d&);
        Vec3d& operator *= (const double);
        Vec3d& operator /= (const double);
        operator Vec3i() const;
        operator Vec3f() const;
    };

    class Vec2 {
    public:
        static int    dot(const Vec2i&, const Vec2i&);
        static float  dot(const Vec2f&, const Vec2f&);
        static double dot(const Vec2d&, const Vec2d&);
        static int    cross(const Vec2i&, const Vec2i&);
        static float  cross(const Vec2f&, const Vec2f&);
        static double cross(const Vec2d&, const Vec2d&);
        static double angle(const Vec2i&, const Vec2i&);
        static double angle(const Vec2f&, const Vec2f&);
        static double angle(const Vec2d&, const Vec2d&);
        static Vec2i xpos();
        static Vec2i xneg();
        static Vec2i ypos();
        static Vec2i yneg();
    private:
        Vec2() = delete;
        Vec2(const Vec2&) = delete;
        Vec2(Vec2&&) = delete;
    };

    class Vec3 {
    public:
        static int    dot(const Vec3i&, const Vec3i&);
        static float  dot(const Vec3f&, const Vec3f&);
        static double dot(const Vec3d&, const Vec3d&);
        static Vec3i  cross(const Vec3i&, const Vec3i&);
        static Vec3f  cross(const Vec3f&, const Vec3f&);
        static Vec3d  cross(const Vec3d&, const Vec3d&);
        static double angle(const Vec3i&, const Vec3i&);
        static double angle(const Vec3f&, const Vec3f&);
        static double angle(const Vec3d&, const Vec3d&);
        static Vec3i xpos();
        static Vec3i xneg();
        static Vec3i ypos();
        static Vec3i yneg();
        static Vec3i zpos();
        static Vec3i zneg();
    private:
        Vec3() = delete;
        Vec3(const Vec3&) = delete;
        Vec3(Vec3&&) = delete;
    };
}

//|-----------------------------------------------------------------
//| [Section] Fundamental Primatives for Rendering and Mathematics
//|-----------------------------------------------------------------

namespace Vi {
    
    class Color;
    class Vertex;
    class Quat;
    class Mat4;
    class Mat4f;

    class Color {
    public:
        float r{}, g{}, b{};
        float a = 1.0f;
        static Color random();
        static Color white();
        static Color black();
        static Color gray();
        static Color red();
        static Color green();
        static Color blue();
        static Color cyan();
        static Color purple();
        static Color yellow();
        Color operator * (float);
    };

    class Vertex {
    public:
        Vec3f position{};
        Color color = Color::white();
        Vec2f tex_coord{};
    };

    class Quat {
    public:
        double w = 1.0;
        double x{}, y{}, z{};
        Quat normalized() const;
        Quat complex_conjugate() const;
        static Quat rotation(const Vec3d&, const double);
        Quat operator * (const Quat&) const;
    };

    class Mat4 {
    public:
        Mat4();
        Mat4(
            double, double, double, double,
            double, double, double, double,
            double, double, double, double,
            double, double, double, double
        );
        static Mat4 scalar_matrix(const double);
        static Mat4 translation_matrix(const Vec3d&);
        static Mat4 rotation_matrix(const Quat&);
        Mat4 operator * (const Mat4&) const;
        explicit operator Mat4f() const;
    private:
        double data[4][4]{};
    };

    class Mat4f {
    public:
        Mat4f();
        float* ptr() const;
    private:
        friend Mat4;
        float data[4][4]{};
    };
}

//|--------------------------------------
//| [Section] Core Rendering Components
//|--------------------------------------

namespace Vi {

    class Mesh;
    class Camera;
    class Mouse;
    class Keyboard;
    class Window;
    class Sprite; // Fwrd Dec

    class Mesh {
    public:
        Mesh();
        Mesh(const Mesh&);
        Mesh(Mesh&&) noexcept;
        Mesh& operator = (const Mesh&);
        Mesh& operator = (Mesh&&) noexcept;
        ~Mesh();
        double scale = 1.0;
        Vec3d position{};
        Quat orientation{};
        std::vector<Vertex> vertices{};
        void paint(const Color&);
        void texture(const std::string & = "");
        void material(const std::string & = "default", const GLenum = GL_TRIANGLES);
    private:
        friend Window;
        std::string texture_path{};
        GLuint texture_id{};
        std::string shader_path{};
        GLuint shader{};
        GLuint primitive{};
        GLuint vao{};
        GLuint vbo{};
        Mat4 model_matrix() const;
        void destroy_texture();
        void destroy_material();
    };

    class Camera {
    public:
        bool infinite_projection = true;
        double far = 100.0;
        double near = 0.1;
        double fov_deg = 70.0;
        Vec3d position{};
        Quat orientation{};
        Vec3d forward() const;
        Vec3d up() const;
        Vec3d right() const;
    private:
        friend Window;
        Mat4 view_matrix() const;
        Mat4 projection_matrix(const Vec2i) const;
    };

    class Mouse {
    public:
        Vec2d position() const;
        Vec2d velocity() const;
        bool pressing(int) const;
        bool pressed(int, int) const;
        double scroll() const;
        void cursor(int);
        bool imgui_captured() const;
    private:
        friend Window;
        static Mouse& get_instance();
        Mouse() = default;
        Mouse(const Mouse&) = delete;
        Mouse(Mouse&&) = delete;
        struct MouseEvent { int button; int action; int mods; };
        struct ScrollEvent { double xoffset; double yoffset; };
        Vec2d pos{}, vel{};
        std::vector<MouseEvent> mouse_events{};
        std::vector<ScrollEvent> scroll_events{};
        void reset();
    };

    class Keyboard {
    public:
        bool pressed(int, int) const;
        bool pressing(int) const;
        bool imgui_captured() const;
    private:
        friend Window;
        static Keyboard& get_instance();
        Keyboard() = default;
        Keyboard(const Keyboard&) = delete;
        Keyboard(Keyboard&&) = delete;
        struct KeyboardEvent { int key; int scancode; int action; int mods; };
        std::vector<KeyboardEvent> keyboard_events{};
        void reset();
    };

    class Window {
    public:
        Window(std::string, int, int);
        ~Window();
        Vec2i size();
        void vsync(bool);
        bool is_open();
        float imgui_scale(float = 0.0f);
        double frame_rate();
        void poll_events();
        void clear(const Color&);
        void draw(const Mesh&, const Camera&);
        void draw(Sprite&);
        void display();
        Mouse& mouse() const;
        Keyboard& keyboard() const;
    private:
        Window(const Window&) = delete;
        Window(Window&&) = delete;
        double track_frame_rate(bool);
        static void callback_window_resize(GLFWwindow*, int, int);
        static void callback_keyboard(GLFWwindow*, int, int, int, int);
        static void callback_mouse(GLFWwindow*, int, int, int);
        static void callback_mousescroll(GLFWwindow*, double, double);
        static inline bool aspect_ratio_changed = false;
    };
}

//|--------------------------------------------------------
//| [Section] Shapes, Sprites, & Text - Derived from Mesh
//|--------------------------------------------------------

namespace Vi {

    class Cube : public Mesh {
    public:
        Cube(int = 0);
    };

    class Sphere : public Mesh {
    public:
        Sphere(int = 10);
        Vec2f screen_position(const Camera&) const;
        float apparent_radius(const Camera&) const;
    };

    class Arrow : public Mesh {
    public:
        Arrow();
    };

    class Sprite : public Mesh {
    public:
        Sprite();
        void set_position(const Vec2i&);
        void set_size(const Vec2f&);
    private:
        friend Window;
        void preserve_aspect_ratio();
        Vec2i screen_position{};
        Vec2i screen_size = Vec2i(100, 100);
        double scale = 1.0;
        Vec3d position{};
        Quat orientation{};
        std::vector<Vertex> vertices{};
    };

    class Text : public Sprite {
    public:
        Text() {}
    };
}

