#include "mat4.h"

#include <memory>
#include <string>
#include <memory.h>
#include <iostream>

Mat4::Mat4() {

    m[0] = { 1.0, 0.0, 0.0, 0.0 };
    m[1] = { 0.0, 1.0, 0.0, 0.0 };
    m[2] = { 0.0, 0.0, 1.0, 0.0 };
    m[3] = { 0.0, 0.0, 0.0, 1.0 };
}

Mat4::Mat4(const Mat4& mat) {

    for (int i = 0; i < SIZE; ++i) {

        m[i] = mat.m[i];
    }
}


Mat4::Mat4(double* m) {

    for (int i = 0; i < 16; i += 4) {

        int index = i / 4;
        this->m[index] = { m[i], m[i + 1], m[i + 2], m[i + 3] };
    }
}

Mat4 Mat4::transpose() {

    Mat4 res;

    for (int i = 0; i < SIZE; ++i) {

        for (int j = 0; j < SIZE; ++j) {

            res[j][i] = m[i][j];
        }
    }

    return res;
}

Mat4 Mat4::inverse() {


    Mat4 n(*this);
    Mat4 o;


    for (int i = 0; i < SIZE - 1; ++i) {

        double divisor = n[i][i];

        for (int j = i + 1; j < SIZE; ++j) {

            double f = n[j][i] / divisor;
            for (int k = 0; k < SIZE; ++k) {

                o[j][k] -= o[i][k] * f;
                n[j][k] -= n[i][k] * f;
            }
        }
    }


    for (int i = SIZE - 1; i > 0; --i) {

        double divisor = n[i][i];

        for (int j = i - 1; j > -1; --j) {

            double f = n[j][i] / divisor;
            for (int k = 0; k < SIZE; ++k) {

                o[j][k] -= o[i][k] * f;
                n[j][k] -= n[i][k] * f;
            }
        }
    }

    for (int i = 0; i < SIZE; ++i) {

        double d = n[i][i];
        for (int j = 0; j < SIZE; ++j) {

            o[i][j] /= d;
            n[i][j] /= d;
        }
    }

    return o;
}

void Mat4::translate(const Vec3& t) {

    m[0][3] += t.x;
    m[1][3] += t.y;
    m[2][3] += t.z;
}


void Mat4::rotate(const Vec3& axis, double angle) {

    double c = cos(angle);
    double s = sin(angle);

    if (axis.x >= 1e-6) {

        m[1][1] = c;
        m[1][2] = -s;

        m[2][1] = s;
        m[2][2] = c;
    }
    else if (axis.y >= 1e-6) {

        m[0][0] = c;
        m[0][2] = s;

        m[2][0] = -s;
        m[2][2] = c;

    }
    else if (axis.z >= 1e-6) {


        m[0][0] = c;
        m[0][1] = -s;

        m[1][0] = s;
        m[1][1] = c;
    }
}

void Mat4::scale(const Vec3& s) {}

Mat4 Mat4::operator*(Mat4& m) {

    Mat4 n = m.transpose();
    Mat4 res;

    for (int i = 0; i < SIZE; ++i) {

        for (int j = 0; j < SIZE; ++j) {

            res[i][j] = dot(this->m[i], n[j]);
        }
    }

    return res;
}

Vec4 Mat4::operator*(const Vec4& v) const {

    Vec4 res;
    res[0] = dot(m[0], v);
    res[1] = dot(m[1], v);
    res[2] = dot(m[2], v);
    res[3] = dot(m[3], v);

    return res;
}

Vec4& Mat4::operator[](int i) {

    assert(i < SIZE);

    return m[i];
}

bool Mat4::operator==(Mat4& m) {

    for (int i = 0; i < SIZE; ++i) {

        for (int j = 0; j < SIZE; ++j) {

            if (this->m[i][j] != m[i][j]) {

            return false;
            }
        }
    }

    return true;
}

void Mat4::print() const {

    printf("mat--------------\n");
    for (int i = 0; i < SIZE; ++i) {

        Vec4 v = (*const_cast<Mat4*>(this))[i];
        printf("%f\t%f\t%f\t%f\n", v.x, v.y, v.z, v.w);
    }
    printf("--------------mat\n\n");
}
