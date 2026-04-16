
/*
    Quaternion.cpp
*/

#include "../Header/Types.h"
#include <cmath>

namespace Vi {

    Quat::Quat(double w, double x, double y, double z) {
        this->w = w;
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Quat Quat::normalized() const {
        double len = std::hypot(x, y, z);
        len = std::hypot(w, len);
        return Quat(
            w / len,
            x / len,
            y / len,
            w / len
        );
    }

    Quat Quat::complex_conjugate() const {
        return Quat(w, -x, -y, -z);
    }

    Quat Quat::operator * (const Quat& other) const {
        const Quat& a = *this;
        const Quat& b = other;
        return Quat(
            (a.w * b.w) - (a.x * b.x) - (a.y * b.y) - (a.z * b.z),
            (a.w * b.x) + (a.x * b.w) + (a.y * b.z) - (a.z * b.y),
            (a.w * b.y) - (a.x * b.z) + (a.y * b.w) + (a.z * b.x),
            (a.w * b.z) + (a.x * b.y) - (a.y * b.x) + (a.z * b.w)
        );
    }
}

