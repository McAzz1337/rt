#ifndef VEC4_H
#define VEC4_H

#include <cassert>
#include <cmath>

struct Vec3;

struct Vec4
{
    double x;
    double y;
    double z;
    double w;
    mutable double len = -1.0;

    Vec4();
    Vec4(const Vec4& v);
    Vec4(double x, double y, double z, double w);

    double angleBetween(const Vec4& v);
    double cosBetween(const Vec4& v);

    double length() const;

    operator Vec3() const;

    inline Vec4 operator+(const Vec4& v) const {

        return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    inline Vec4 operator-(const Vec4& v) const {

        return Vec4(x - v.x, y - v.y, z - v.z, w - v.z);
    }

    inline Vec4 operator*(double d) const {

        return Vec4(x * d, y * d, z * d, w * d);
    }

    inline void operator=(const Vec4& v) {

        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
    }

    inline Vec4 normalized() const {

        Vec4 v;

        if (len <= -1.0) {

            length();
        }

        double inv = 1.0 / len;

        v.x = x * inv;
        v.y = y * inv;
        v.z = z * inv;
        v.w = w * inv;

        return v;
    }

    inline double& operator[](int i) {

        assert(i < 4);

        switch (i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        }

        return x;
    }

};


inline Vec4 operator*(double d, const Vec4 v) {

    return v * d;
}

inline double dot(const Vec4& a, const Vec4& b) {

    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline Vec4 cross(const Vec4& a, const Vec4& b) {

    return Vec4(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x,
        0.0
    );
}







#endif // VEC4_H
