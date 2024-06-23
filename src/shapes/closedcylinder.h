#ifndef CLOSEDCYLINDER_H
#define CLOSEDCYLINDER_H

#include "cylinder.h"
#include "disc.h"

class ClosedCylinder: public Object
{
    Cylinder c;
    Disc top;
    Disc bottom;

public:
ClosedCylinder();
ClosedCylinder(const ClosedCylinder& c);
ClosedCylinder(const Vec3& pos, Material* mat, double radius, double height);

virtual bool hit(const Ray& ray, PoI& poi) override;

};

#endif // CLOSEDCYLINDER_H
