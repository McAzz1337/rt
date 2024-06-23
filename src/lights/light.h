#ifndef LIGHT_H
#define LIGHT_H

#include "math/vec3.h"

struct Light
{


    Vec3 position;

    Light(const Vec3& position);
    Light(const Light& l);

    virtual double intensity(const Vec3& point, const Vec3& normal, double ambient) const = 0;
    virtual bool inLight(const Vec3& point, const Vec3& normal) const = 0;

};

#endif // LIGHT_H
