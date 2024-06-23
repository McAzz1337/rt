#include "vec3.h"
#include "cmath"

#include "vec4.h"

Vec3::Vec3() : x(1.0), y(1.0), z(1.0) {}

Vec3::Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

double Vec3::angleBetween(const Vec3& v) const {

    return acos(cosBetween(v));
}


double Vec3::cosBetween(const Vec3& v) const {

    double divisor = dot(*this, v);
    double dividend = length() * v.length();

    return divisor / dividend;
}



double Vec3::length() const {

    if (len >= -1e-6) {

        return len;
    }

    len = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    return len;
}

Vec3 Vec3::operator-() const {

    return -1.0 * (*this);
}

    Vec3 Vec3::operator+(const Vec3& v) const {

        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    Vec3 Vec3::operator-(const Vec3& v) const {

        return Vec3(x - v.x, y - v.y, z - v.z);
    }


    Vec3 Vec3::operator*(const Vec3& v) const {

        return Vec3(x * v.x, y * v.y, z * v.y);
    }

    Vec3 Vec3::operator/(double d) const {

        return Vec3(x / d, y / d, z / d);
    }

    Vec3 Vec3::operator*(double d) const {

        return Vec3(x * d, y * d, z * d);
    }

    void Vec3::operator=(const Vec3& v) {

        x = v.x;
        y = v.y;
        z = v.z;
    }


    bool Vec3::operator==(const Vec3& v) const {

        return x == v.x && y == v.y && z == v.z;
    }

    Vec3 Vec3::normalized() const {

        Vec3 v;

        if (len <= 1e-6) {

            length();
        }

        double inv = 1.0 / len;

        v.x = x * inv;
        v.y = y * inv;
        v.z = z * inv;

        return v;
    }


Vec3::operator Vec4() const {

    return Vec4(x, y, z, 1.0);
}


Vec3 operator*(double d, const Vec3 v) {

    return v * d;
}

Vec3 abs(const Vec3& v) {

    return Vec3(abs(v.x), abs(v.y), abs(v.z));
}

double dist(const Vec3& a, const Vec3& b) {

    return abs(a - b).length();
}

double dot(const Vec3& a, const Vec3& b) {

    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 cross(const Vec3& a, const Vec3& b) {

    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

Vec3 reflect (const Vec3 & v, const Vec3 & n) {

    return 2 * dot (v, n) * n - v;
}

double determinant (const Vec3 & u, const Vec3 & v, const Vec3 & w) {

    return dot (cross (u, v), w);
}
