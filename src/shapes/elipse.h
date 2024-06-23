#ifndef ELISPE_H
#define ELISPE_H

#include "object.h"

class Elipse: public Object
{

    double radiusA;
    double radiusB;

public:
    Elipse();
    Elipse(const Elipse& e);
    Elipse(const Vec3& position, Material* mat,  double radiusA, double radiusB);

    virtual bool hit(const Ray& ray, PoI& poi) override;
};

#endif // ELISPE_H
