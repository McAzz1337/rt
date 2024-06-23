#ifndef RAY_H
#define RAY_H

#include "vec3.h"

struct Ray
{
    const Vec3 origin;
    const Vec3 dir;

    Ray(const Vec3& origin, const Vec3& dir);

    inline Vec3 point(double lambda) const {

        return origin + lambda * dir;
    }
};

#endif // RAY_H
