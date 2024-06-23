#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "object.h"
#include "triangle.h"

class Crystal: public Object
{
    static constexpr int TRI_COUNT = 20;
    Triangle tris[TRI_COUNT];
    double radius;
    double baseHeight;
    double pointHeight;

public:
    Crystal();
    Crystal(const Crystal& c);
    Crystal(const Vec3& pos, Material* mat, double radius, double baseHeight, double pointHeight);

    virtual bool hit(const Ray& ray, PoI& poi);
};

#endif // CRYSTAL_H
