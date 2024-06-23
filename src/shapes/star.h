#ifndef STAR_H
#define STAR_H

#include "object.h"
#include "triangle.h"



class Star: public Object
{
    constexpr static int TRI_COUNT = 15;
    Triangle tris[TRI_COUNT];
    double triSize;

public:
    Star();
    Star(const Star& s);
    Star(const Vec3 pos, Material* mat, double triSize);

    virtual bool hit(const Ray& ray, PoI& poi) override;
};

#endif // STAR_H
