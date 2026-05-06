
/*
    demo.cpp
*/

#include "Violet/Rendering.h"
#include "Violet/Shapes.h"
#include "Violet/Logging.h"

static void control_camera(Vi::Camera&, Vi::Window&);
static void demo_gui(Vi::Window&);

int main() {

    Vi::Window window = Vi::Window("Application", 1920, 1080);
    window.imgui_scale(2.0f);
    
    Vi::Camera camera{};
    camera.position = Vi::Vec3d(0, 0, 2);

    Vi::Sphere sphere{};

    while (window.is_open()) {
        window.poll_events();
        window.clear(Vi::Color::blue());
        control_camera(camera, window);
        demo_gui(window);
        window.draw(sphere, camera);
        window.display();
    }

    return 0;
}

static void control_camera(Vi::Camera& camera, Vi::Window& window) {
    Vi::Keyboard& keyboard = Vi::Window::keyboard();
    double frame_rate = window.frame_rate();
    double speed = 5.0 * (1.0 / frame_rate);

    if (keyboard.pressing(GLFW_KEY_W)) { camera.position += camera.forward() * speed; }
    if (keyboard.pressing(GLFW_KEY_A)) { camera.position += camera.right() * -speed; }
    if (keyboard.pressing(GLFW_KEY_S)) { camera.position += camera.forward() * -speed; }
    if (keyboard.pressing(GLFW_KEY_D)) { camera.position += camera.right() * speed; }

    if (keyboard.pressing(GLFW_KEY_SPACE))      { camera.position += Vi::Vec3d::ypos() * speed; }
    if (keyboard.pressing(GLFW_KEY_LEFT_SHIFT)) { camera.position += Vi::Vec3d::yneg() * speed; }

    Vi::Mouse& mouse = Vi::Window::mouse();

    if (mouse.pressed(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS)) { Vi::Log::print("pressed!\n"); mouse.cursor(GLFW_CURSOR_DISABLED); }
    if (mouse.pressed(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE)) { Vi::Log::print("released!\n"); mouse.cursor(GLFW_CURSOR_NORMAL); }

    if (mouse.pressing(GLFW_MOUSE_BUTTON_LEFT)) {        
        double sensitivity = 0.1 * (1.0 / frame_rate);
        double x_movement = mouse.velocity().x;
        double y_movement = mouse.velocity().y;
        // Lateral Rotation
        Vi::Vec3d up = Vi::Vec3d::ypos();
        Vi::Quat lateral_rotation = Vi::Quat::rotation(up, sensitivity * -x_movement);
        camera.orientation = lateral_rotation * camera.orientation;
        // Longitudinal Rotation
        Vi::Vec3d right = camera.right();
        Vi::Quat longitudinal_rotation = Vi::Quat::rotation(right, sensitivity * -y_movement);
        camera.orientation = longitudinal_rotation * camera.orientation;
        camera.orientation = camera.orientation.normalized();
    }


}

static void demo_gui(Vi::Window& window) {
    ImGui::Begin("The demo gui");
    if (ImGui::Button("Enable VSync")) {
        window.vsync(true);
    }
    if (ImGui::Button("Disable VSync")) {
        window.vsync(false);
    }
    ImGui::End();
}

