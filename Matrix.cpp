
/*
    Matrix.cpp
*/

#include "Types.h"

namespace Vi {
    
    /* Public */

    Mat4::Mat4() {
        *this = Mat4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
    }

    Mat4 Mat4::scalar_matrix(const double s) {
        return Mat4(
            s, 0, 0, 0,
            0, s, 0, 0,
            0, 0, s, 0,
            0, 0, 0, 1
        );
    }

    Mat4 Mat4::translation_matrix(const Vec3d& p) {
        return Mat4(
            1, 0, 0, p.x,
            0, 1, 0, p.y,
            0, 0, 1, p.z,
            0, 0, 0, 1
        );
    }

    Mat4 Mat4::rotation_matrix(const Quat& q) {
        return Mat4(
            
        );
    }

    Mat4 Mat4::operator * (const Mat4& matrix) const {

    }
    
    /* Private */

    Mat4::Mat4(
        double a, double b, double c, double d,
        double e, double f, double g, double h,
        double i, double j, double k, double l,
        double m, double n, double o, double p
    ) {
        data[0][0] = a; data[0][1] = b; data[0][2] = c; data[0][3] = d;
        data[1][0] = e; data[1][1] = f; data[1][2] = g; data[1][3] = h;
        data[2][0] = i; data[2][1] = j; data[2][2] = k; data[2][3] = l;
        data[3][0] = m; data[3][1] = n; data[3][2] = o; data[3][3] = p;
    }
}

