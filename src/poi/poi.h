#ifndef POI_H
#define POI_H

#include "math/vec3.h"
#include "surface/material.h"
#include "rgb.h"

class Object;

struct  PoI
{

    bool exists = false;
    Object* object;
    Vec3 point;
    Vec3 normal;
    double lambda = pow(2, 63);

    PoI();
    
    void adjust(const Vec3& point, double lambda, const Vec3& normal, Object* object);
};

#endif // POI_H
