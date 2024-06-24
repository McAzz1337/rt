#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cassert>

#include "rgb.h"

struct Vec4;

struct Vec3 {

    double x, y, z;
    mutable double len = -1.0;

    Vec3();
    Vec3(const Vec3& v);
    Vec3(double x, double y, double z);

    double angleBetween(const Vec3& v) const;
    double cosBetween(const Vec3& v) const;

    double length() const;

    operator Vec4() const;

    Vec3 operator-() const;

    Vec3 operator+(const Vec3& v) const;

    Vec3 operator-(const Vec3& v) const;

    Vec3 operator*(const Vec3& v) const;

    Vec3 operator*(double d) const;

    Vec3 operator/(double d) const;

    void operator=(const Vec3& v);

    bool operator==(const Vec3& v) const;

    Vec3 normalized() const;

    inline operator RGB() {

        return RGB(x, y, z);
    }

    inline void print() const {

        printf("%f\t%f\t%f\n", x, y, z);
    }

    inline double& operator[](int i) {

        assert(i < 3);

        switch (i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        }

        return x;
    }

};

std::ostream& operator<<(std::ostream& o, const Vec3& v);

Vec3 operator*(double d, const Vec3 v);

Vec3 abs(const Vec3& v);

double dist(const Vec3& a, const Vec3& b);

double dot(const Vec3& a, const Vec3& b);

Vec3 cross(const Vec3& a, const Vec3& b);

Vec3 reflect (const Vec3 & v, const Vec3 & n);

double determinant (const Vec3 & u, const Vec3 & v, const Vec3 & w);


#endif // VEC3_H
