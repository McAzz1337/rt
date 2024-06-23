#ifndef CYLINDER_H
#define CYLINDER_H

#include "object.h"

class Cylinder: public Object
{

    double radius;
    double height;
    bool aggregated = false;

public:
    Cylinder();
    Cylinder(const Cylinder& c);
    Cylinder(const Vec3& pos, double radius, double height);
    Cylinder(const Vec3& pos, Material* mat, double radius, double height);

    virtual bool hit(const Ray& ray, PoI& poi) override;

};

#endif // CYLINDER_H
