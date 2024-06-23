#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "math/vec3.h"
#include "math/mat4.h"
#include <cassert>
#include "math/ray.h"
#include "poi/poi.h"

class Triangle
{

    Vec3 a;
    Vec3 b;
    Vec3 c;
    Vec3 position;

public:
    Triangle();
    Triangle(const Triangle& t);
    Triangle(const Vec3& a, const Vec3& b,const Vec3& c);

    bool hit(const Ray& ray, PoI& poi);

    inline void translate(const Mat4& m) {

        a = m * a;
        b = m * b;
        c = m * c;
        position = (a + b + c) / 3.0;
    }

    inline Vec3 operator[](int i) {

        assert(i < 3);

        switch (i) {
        case 0: return a;
        case 1: return b;
        case 2: return c;
        }

        return Vec3(0.0, 0.0, 0.0);
    }

    Vec3 getNormal() const;

    inline const Vec3& getPosition() const {

        return position;
    }

    inline void print(const char* name) {

        Vec3 n = getNormal();
        printf("%s n:\t%f\t%f\t%f\n", name, n.x, n.y, n.z);
    }

};

#endif // TRIANGLE_H
