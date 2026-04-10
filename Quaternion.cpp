
/*
    Quaternion.cpp
*/

#include "Types.h"
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

    Quat operator * (const Quat& other) {

    }
}

