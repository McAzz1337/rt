#ifndef SPHERE_H
#define SPHERE_H


#include "object.h"
#include "math/vec3.h"
#include "math/ray.h"

class Sphere: public Object {

    double radius;
public:

    Sphere();
    Sphere(const Sphere& s);
    Sphere(const Vec3& pos, double radius, Material* mat);

    bool hit(const Ray& ray, PoI& poi) override;


    inline double getRadius() const {

        return radius;
    }

    inline void operator=(const Sphere& s) {

        this->position = s.getPosition();
        radius = s.radius;
        mat = s.mat;
    }

};

#endif // SPHERE_H
