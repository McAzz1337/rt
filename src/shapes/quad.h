#ifndef QUAD_H
#define QUAD_H

#include "object.h"
#include "triangle.h"

class Quad: public Object
{

    Triangle a;
    Triangle b;
    double size;

public:
    Quad();
    Quad(const Quad& q);
    Quad(const Vec3& pos, Material* mat, double size);

    virtual bool hit(const Ray& ray, PoI& poi) override;
};

#endif // QUAD_H
