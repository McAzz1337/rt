#ifndef DISC_H
#define DISC_H


#include "object.h"

class Disc: public Object
{

    double radius;
    Vec3 normal;
    bool aggregated = false;

public:
    Disc();
    Disc(const Disc& d);
    Disc(const Vec3& pos, double radius, const Vec3& normal);
    Disc(const Vec3& pos, Material* mat, double radius, const Vec3& normal);

    virtual bool hit(const Ray& ray, PoI& poi) override;
};

#endif // DISC_H
