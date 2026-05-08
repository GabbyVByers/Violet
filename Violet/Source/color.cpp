
/*
    color.cpp
*/

#include "../rendering.h"
#include <cstdlib>

namespace Vi {

    /* Public */
    
    Color Color::random() {
        return Color(
            (float)std::rand() / (float)RAND_MAX,
            (float)std::rand() / (float)RAND_MAX,
            (float)std::rand() / (float)RAND_MAX
        );
    }

    Color Color::white()  { return Color(1.0, 1.0, 1.0); }
    Color Color::black()  { return Color(0.0, 0.0, 0.0); }
    Color Color::gray()   { return Color(0.5, 0.5, 0.5); }
    Color Color::red()    { return Color(1.0, 0.0, 0.0); }
    Color Color::green()  { return Color(0.0, 1.0, 0.0); }
    Color Color::blue()   { return Color(0.0, 0.0, 1.0); }
    Color Color::cyan()   { return Color(0.0, 1.0, 1.0); }
    Color Color::purple() { return Color(1.0, 0.0, 1.0); }
    Color Color::yellow() { return Color(1.0, 1.0, 0.0); }

    Color Color::operator * (float brightness) {
        float r = std::min(std::max(0.0f, this->r * brightness), 1.0f);
        float g = std::min(std::max(0.0f, this->g * brightness), 1.0f);
        float b = std::min(std::max(0.0f, this->b * brightness), 1.0f);
        return Color(r, g, b, this->a);
    }
}

