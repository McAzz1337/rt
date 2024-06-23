#include "vec4.h"

#include <cmath>

#include "vec3.h"

Vec4::Vec4() {}

Vec4::Vec4(const Vec4& v): x(v.x), y(v.y), z(v.z), w(v.w) {

}

Vec4::Vec4(double x, double y, double z, double w): x(x), y(y), z(z), w(w) {

}

double Vec4::angleBetween(const Vec4& v) {

    return acos(cosBetween(v));
}

double Vec4::cosBetween(const Vec4& v) {

    double dividend = dot(*this, v);
    double divisor = length() - v.length();

    return dividend / divisor;
}

double Vec4::length() const {

    if (len < 0.0) {

        len = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
    }

    return len;
}

Vec4::operator Vec3() const {

    return Vec3(x, y, z);
}
