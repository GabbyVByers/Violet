
/*
    sprite.cpp
*/

#include "../rendering.h"
#include "../logging.h"

namespace Vi {

    Sprite::Sprite() {
        set_position(screen_position);
        set_size(screen_size);
    }

    void Sprite::set_position(const Vec2i& pos) {
        screen_position = pos;
        GLFWwindow* window = glfwGetCurrentContext();
        if (window == nullptr) {
            Log::error("Sprite position cannot be set without an active viewport!");
        }
        Vec2i window_dimensions{};
        glfwGetFramebufferSize(window, &window_dimensions.x, &window_dimensions.y);

        float x = ((((float)screen_position.x / (float)window_dimensions.x) * 2.0f) - 1.0f);
        float y = (1.0f - (((float)screen_position.y / (float)window_dimensions.y) * 2.0f));

        vertices.clear();
        Vec2f true_screen_size = static_cast<Vec2f>(screen_size);
        true_screen_size.x /= (float)window_dimensions.x;
        true_screen_size.y /= (float)window_dimensions.y;
        Vertex tl = Vertex(Vec3f(x, y, 0.0f), Color::white(), Vec2f(0.0f, 0.0f));
        Vertex tr = Vertex(Vec3f(x + (float)true_screen_size.x, y, 0.0f), Color::white(), Vec2f(1.0f, 0.0f));
        Vertex bl = Vertex(Vec3f(x, y - (float)true_screen_size.y, 0.0f), Color::white(), Vec2f(0.0f, -1.0f));
        Vertex br = Vertex(Vec3f(x + (float)true_screen_size.x, y - (float)true_screen_size.y, 0.0f), Color::white(), Vec2f(1.0f, -1.0f));
        std::vector<Vertex> quad = { tl, tr, bl, tr, br, bl };
        vertices.insert(vertices.end(), quad.begin(), quad.end());
    }

    void Sprite::set_size(const Vec2f& size) {
        screen_size = size;
        set_position(screen_position);
    }

    void Sprite::preserve_aspect_ratio() {
        GLFWwindow* window = glfwGetCurrentContext();
        Vec2i window_dimensions{};
        glfwGetFramebufferSize(window, &window_dimensions.x, &window_dimensions.y);

        float x = ((((float)screen_position.x / (float)window_dimensions.x) * 2.0f) - 1.0f);
        float y = (1.0f - (((float)screen_position.y / (float)window_dimensions.y) * 2.0f));

        vertices.clear();
        Vec2f true_screen_size = static_cast<Vec2f>(screen_size);
        true_screen_size.x /= (float)window_dimensions.x;
        true_screen_size.y /= (float)window_dimensions.y;
        Vertex tl = Vertex(Vec3f(x, y, 0.0f), Color::white(), Vec2f(0.0f, 0.0f));
        Vertex tr = Vertex(Vec3f(x + (float)true_screen_size.x, y, 0.0f), Color::white(), Vec2f(1.0f, 0.0f));
        Vertex bl = Vertex(Vec3f(x, y - (float)true_screen_size.y, 0.0f), Color::white(), Vec2f(0.0f, -1.0f));
        Vertex br = Vertex(Vec3f(x + (float)true_screen_size.x, y - (float)true_screen_size.y, 0.0f), Color::white(), Vec2f(1.0f, -1.0f));
        std::vector<Vertex> quad = { tl, tr, bl, tr, br, bl };
        vertices.insert(vertices.end(), quad.begin(), quad.end());
    }
}

